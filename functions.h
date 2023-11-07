#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

void Error(const std::string& _command) {
    std::cout << "Wrong parameter:\n" << _command;
    exit(0);
}

void PathToScores(const char* _path, const std::string& _filename, std::string& _filepath) {
    _filepath = _path;
    _filepath.erase((_filepath.rfind("\\") + 1));
    _filepath += _filename;
}

void PrintTable(const std::string& _filepath) {

    std::ifstream _file(_filepath);
    std::string _line;
    std::string _tmp_name;
    int _tmp_score;
    std::vector<std::string> _name;
    std::vector<int> _score;
    bool _sorted = false;

    if (_file.is_open()) {
        while (std::getline(_file, _line)) {

            //парсим данные для сортировки
            size_t _pos = _line.find(" ");
            _name.push_back(_line.substr(0, _pos));
            _score.push_back(stoi(_line.substr(_pos, (_line.size() - _pos))));
        }


        //сортируем пузырьком по очкам
        for (int i = 1; i < _name.size(); ++i)
        {
            for (int j = 0; j < _name.size() - i; ++j)
            {
                if (_score[j] > _score[j + 1])
                {

                    _tmp_score = _score[j];
                    _score[j] = _score[j + 1];
                    _score[j + 1] = _tmp_score;

                    _tmp_name = _name[j];
                    _name[j] = _name[j + 1];
                    _name[j + 1] = _tmp_name;
                }
            }
        }

        std::cout << "Table of records:" << std::endl;
        std::cout << "Name\t\tScore" << std::endl << std::endl;
        for (int i = 0; i < _name.size(); ++i) {
            std::cout << _name[i];
            std::cout << "\t\t\t" << _score[i] << std::endl;
        }
        exit(0);
    }
    else {
        std::cout << "File not exist! Exit.";
        exit(0);
    }
}

void SetMaxNumber(const std::string& _command, int& _parameter) {
    size_t _pos = _command.find("=") + 1;
    if (_pos != 0) {
        _parameter = (stoi(_command.substr(_pos, (_command.size() - _pos))));
        std::cout << "Max value changed to: " << _parameter << "\n";
    }
    else {
        Error(_command);
    }
}

void SetMaxLevel(const std::string& _command, int& _parameter) {

    int _level = 0;
    size_t _pos = _command.find("=") + 1;

    if (_pos != 0) {

        _level = (stoi(_command.substr(_pos, (_command.size() - _pos))));
        if (_level == 1) {
            _parameter = 10;
            std::cout << "Max value changed to: " << _parameter << "\n";
        } else if (_level == 2) {
            _parameter = 50;
            std::cout << "Max value changed to: " << _parameter << "\n";
        } else if (_level == 3) {
            _parameter = 100;
            std::cout << "Max value changed to: " << _parameter << "\n";
        }
        else Error(_command);
    }
    else {
        Error(_command);
    }
}

void SetRandomValue(int& _random_value, const int& _max_value) {
    std::srand(std::time(nullptr));
    _random_value = std::rand() % _max_value;
    std::cout << "I guessed value: " << _random_value << "\n";
}

void SetPlayerName(std::string& _player_name) {
    std::cout << "Hello!\n";
    std::cout << "I want to play a game\n";
    std::cout << "it's called \"Guess the number\"\n";
    std::cout << "Enter your name: ";
    std::cin >> _player_name;
    std::cout << "Perfect! Your name is " << _player_name << "\n";
}

void StartGame(const int& _max_value, const int& _value, int& _number, int& _count) {

    std::cout << "I guessed some number from 0 to " << _max_value << " and your task is to guess it\n";
    std::cout << "the number of attempts is not limited, so let's start\n";

    for (;;) {

        std::cout << "what number did i guess?: ";
        std::cin >> _number;

        if (!std::cin.good() || std::cin.eof()) {

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Oops, that input is invalid.  Please try again.\n";

        }
        else {

            ++_count;
            if (_number == _value) break;
            if (_number > _value) std::cout << "No, you are not guess, my number is less than you enter. Try again.\n";
            else std::cout << "No, you are not guess, my number is greater than you enter. Try again.\n";
            
        }
    }
    
    std::cout << "Congratulations, you guessed right on the " << _count <<" try.\n";
}

void SaveTable(const std::string& _filepath, const std::string& _player_name, const int& _count) {
    std::ifstream _file(_filepath);
    std::string _line;
    std::vector<std::string> _name;
    std::vector<int> _score;
    bool _change_score = false;

    if (_file.is_open()) {
        while (std::getline(_file, _line)) {

            size_t _pos = _line.find(" ");
            _name.push_back(_line.substr(0, _pos));
            _score.push_back(stoi(_line.substr(_pos, (_line.size() - _pos))));
        }


        for (int i = 0; i < _name.size(); ++i) {

            if (_name[i] == _player_name && _score[i] > _count) {

                _score[i] = _count;
                _change_score = true;

            }
        }

        if (!_change_score) {
            _name.push_back(_player_name);
            _score.push_back(_count);
        }

        _file.close();

    }

        std::ofstream _file_out(_filepath);
        for (int i = 0; i < _name.size(); ++i) {
            _line = _name[i] + " " + std::to_string(_score[i]);
            _file_out << _line << std::endl;
        }

        _file_out.close();
    }