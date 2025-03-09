const readline = require('readline');
const os = require('os');
const process = require('process');

class SamITOS {
    constructor() {
        this.processes = {};
        this.files = {};
        this.nextProcessId = 1;
        this.commands = {
            poweroff: this.poweroff,
            reboot: this.reboot,
            echo: this.echo,
            ls: this.ls,
            cr_fl: this.cr_fl,
            dl_fl: this.dl_fl,
            read: this.read_file,
            write: this.write_file,
            cr_proc: this.cr_proc,
            dl_proc: this.dl_proc,
            nicopat: this.nicopat,
            ps: this.ps,
            clear: this.clear,
            help: this.help,
            exit: () => process.exit(0),
        };
    }

    run_command(command) {
        const args = command.trim().split(" ");
        const cmd = args[0];
        if (!this.commands[cmd]) {
            console.log(`Команда '${cmd}' не найдена.`);
            return;
        }
        this.commands[cmd].apply(this, args.slice(1));
    }

    poweroff() {
        console.log("Выключение ПК...");
        process.exit(0);
    }

    reboot() {
        console.log("Перезагрузка ОС...");
        this.processes = {};
        this.files = {};
        this.nextProcessId = 1;
    }

    echo(...message) {
        console.log(message.join(" "));
    }

    ls() {
        console.log("Файлы в виртуальной папке:");
        console.log(Object.keys(this.files).length ? Object.keys(this.files).join("\n") : "(пусто)");
    }

    cr_fl(filename) {
        if (!filename) return console.log("Ошибка: укажите имя файла.");
        if (this.files.hasOwnProperty(filename)) return console.log(`Файл ${filename} уже существует.`);
        this.files[filename] = "";
        console.log(`Файл ${filename} создан.`);
    }

    dl_fl(filename) {
        if (!filename) return console.log("Ошибка: укажите имя файла.");
        if (!this.files.hasOwnProperty(filename)) return console.log(`Файл ${filename} не найден.`);
        delete this.files[filename];
        console.log(`Файл ${filename} удален.`);
    }

    read_file(filename) {
        if (!filename) return console.log("Ошибка: укажите имя файла.");
        filename = filename.trim();
        if (!this.files.hasOwnProperty(filename)) return console.log(`Файл ${filename} не найден.`);
        console.log(`Содержимое файла ${filename}:`);
        console.log(this.files[filename] || "(пусто)");
    }

    write_file(filename, ...text) {
        if (!filename || text.length === 0) return console.log("Ошибка: укажите имя файла и текст.");
        filename = filename.trim();
        if (!this.files.hasOwnProperty(filename)) return console.log(`Файл ${filename} не найден.`);
        this.files[filename] += (this.files[filename] ? "\n" : "") + text.join(" ");
        console.log(`Запись добавлена в файл ${filename}.`);
    }

    cr_proc(processName) {
        if (!processName) return console.log("Ошибка: укажите имя процесса.");
        this.processes[this.nextProcessId] = { name: processName };
        console.log(`Процесс ${processName} создан с ID ${this.nextProcessId}.`);
        this.nextProcessId++;
    }

    dl_proc(processId) {
        const id = Number(processId);
        if (isNaN(id) || !this.processes[id]) return console.log(`Процесс с ID ${processId} не найден.`);
        delete this.processes[id];
        console.log(`Процесс с ID ${id} удален.`);
    }

    nicopat() {
        console.log("Информация о системе:");
        console.log("ОС: SAMITOS BETA VERSION");
        console.log(`Архитектура: ${os.arch()}`);
        console.log(`Процессор: ${os.cpus()[0].model}`);
        console.log(`Количество ядер: ${os.cpus().length}`);
        console.log(`Оперативная память: ${(os.totalmem() / 1024 / 1024 / 1024).toFixed(2)} ГБ`);
    }

    ps() {
        console.log("Активные процессы:");
        if (Object.keys(this.processes).length === 0) {
            console.log("(нет активных процессов)");
        } else {
            Object.entries(this.processes).forEach(([id, proc]) => {
                console.log(`ID: ${id}, Имя: ${proc.name}`);
            });
        }
    }

    clear() {
        console.clear();
    }

    help() {
        console.log("Доступные команды:");
        console.log(Object.keys(this.commands).map(cmd => `${cmd} - ${this.getCommandDescription(cmd)}`).join("\n"));
    }

    getCommandDescription(cmd) {
        const descriptions = {
            poweroff: "Выключить ПК",
            reboot: "Перезагрузить ОС",
            echo: "Вывести текст",
            ls: "Показать файлы",
            cr_fl: "Создать файл",
            dl_fl: "Удалить файл",
            read: "Прочитать файл",
            write: "Записать в файл",
            cr_proc: "Создать процесс",
            dl_proc: "Удалить процесс",
            nicopat: "Характеристики ПК",
            ps: "Показать активные процессы",
            clear: "Очистить экран",
            help: "Показать справку",
            exit: "Выйти из SamITOS",
        };
        return descriptions[cmd] || "Описание недоступно";
    }
}

if (require.main === module) {
    const rl = readline.createInterface({ input: process.stdin, output: process.stdout });
    const osInstance = new SamITOS();
    console.log("---SamITOS BETA VERSION---");
    rl.setPrompt("SamITOS$> ");
    rl.prompt();
    rl.on("line", (input) => {
        osInstance.run_command(input);
        rl.setPrompt("SamITOS$> ");
        rl.prompt();
    });
}
