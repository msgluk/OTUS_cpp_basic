#include "functions.h"

#include <iostream>
#include <cstdlib>
#include <fstream>

//структура для параметров. просто удобно всё в одном месте держать
struct Settings {

    int _max_value = 10;

    int _random_value = -1;

    int _player_number = -1;

    int _player_count = 0;

    //путь до файла с очками
    std::string _scores_storage = "";

    //название файла с очками
    std::string _scores_filename = "scores.txt";

    std::string _player_name = "";

    bool _find_max = false;

    bool _find_level = false;


} _settings;

int main(int argc, char* argv[]) {

    //тут мы формируем полный путь до файла с очками, из текущей папки иногда не открывает
    //сделаем так чтобы гарантированно открылся в любом случае
    PathToScores(argv[0], _settings._scores_filename, _settings._scores_storage);

    //парсим командную строку в цикле
    //ищем параметр table чтобы вывести таблицу рекордов и завершить работу
    //если находим max и level то завершаем работу
    //если всё ок, меняем max_value
    for (int _iter = 0; _iter < argc; ++_iter) {

        //преобразуем массив символов в строку (так проще парсить средствами string)
        std::string _command = argv[_iter];

        //если искомая подстрока не найдена, то вернется npos
        //в С++23 есть функция contains, но мы пользуемся 17м. что есть, то есть.
        if (_command.find("table") != std::string::npos) {

            PrintTable(_settings._scores_storage);
        }

        if (_command.find("max") != std::string::npos) _settings._find_max = true;
        if (_command.find("level") != std::string::npos) _settings._find_level = true;

        if (_settings._find_level && _settings._find_max) {

            Error(_command);

        }

        if (_command.find("max") != std::string::npos) {

            SetMaxNumber(_command, _settings._max_value);
        }

        if (_command.find("level") != std::string::npos) {

            SetMaxLevel(_command, _settings._max_value);
        }
    }

    SetRandomValue(_settings._random_value, _settings._max_value);

    SetPlayerName(_settings._player_name);

    StartGame(_settings._max_value, _settings._random_value, _settings._player_number, _settings._player_count);

    SaveTable(_settings._scores_storage, _settings._player_name, _settings._player_count);

    PrintTable(_settings._scores_storage);

    return 0;
}