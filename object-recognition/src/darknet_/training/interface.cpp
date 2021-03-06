#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

void printMenu()
{
    string logo = "\n\t\t    _/_/_/_/        _/_/_/  _/    _/  _/      _/    _/_/_/        _/      _/_/_/    _/_/_/      _/_/    _/      _/    _/_/_/  _/    _/   \n"
                  "\t\t   _/            _/        _/    _/    _/  _/    _/            _/_/      _/    _/  _/    _/  _/    _/  _/_/    _/  _/        _/    _/    \n"
                  "\t\t  _/_/_/        _/  _/_/  _/    _/      _/        _/_/          _/      _/_/_/    _/_/_/    _/_/_/_/  _/  _/  _/  _/        _/_/_/_/     \n"
                  "\t\t       _/      _/    _/  _/    _/      _/            _/        _/      _/    _/  _/    _/  _/    _/  _/    _/_/  _/        _/    _/      \n"
                  "\t\t_/_/_/          _/_/_/    _/_/        _/      _/_/_/          _/      _/_/_/    _/    _/  _/    _/  _/      _/    _/_/_/  _/    _/ \n";

    cout << "\033[2J"; // Clear screen;
    cout << "\033[0;0H"; // Move cursor to top left
    cout << "\033[36m";
    printf(logo.c_str());
    cout << "\033[37m";

    cout << "\n1. Test image\n" << "2. Test demo video\n" << "3. Mark images\n" << "4. Train on marked images\n" << "5. Quit\n" << "---------------------------------\nChoice: ";
    cout.flush();
}

int main()
{
    printMenu();

    int choice;
    cin >> choice;

    string weights, config;
    string data, train, classes;

    while(choice != 5)
    {
        getline(cin, data); // get rid of data in buffer

        switch(choice)
        {
            case 1:
            cout << "Weights (default = backup/animals_last.weights): " << endl;
            getline(cin, weights);

            if(weights == "\n")
                weights = "backup/animals_last.weights";

            cout << "Config (default = cfg/animals.cfg): " << endl;
            getline(cin, config);

            if(config == "\n")
                config = "cfg/animals.cfg";

            cout << "Image to test (path from darknet_ director): " << endl;
            getline(cin, data);

            chdir("..");
            system(("./darknet detect cfg/animals.cfg backup/animals_last.weights " + data).c_str());
            chdir("training");

            break;

            case 2:
                cout << "Weights (default = backup/animals_last.weights): " << endl;
                getline(cin, weights);

                if(weights == "\n")
                    weights = "backup/animals_last.weights";

                cout << "Config (default = cfg/animals.cfg): " << endl;
                getline(cin, config);

                if(config == "\n")
                    config = "backup/animals_last.weights";

                cout << "Video to test (path from darknet_ director): " << endl;
                getline(cin, data);

                chdir("..");
                system(("./darknet detector demo cfg/animals.data cfg/animals.cfg backup/animals_last.weights " + data).c_str());
                chdir("training");

                break;

            case 3:
                cout << "Images directory (default = ../darkent/data/animal-images): " << endl;
                getline(cin, data);

                if(data == "\n")
                    data = "../data/animal-images";

                cout << "Training file (default = ../data/train.txt): " << endl;
                getline(cin, train);

                if(train == "\n")
                    train = "../data/train.txt";

                cout << "Training file (default = ../data/animal-classes.names): " << endl;
                getline(cin, classes);

                if(classes == "\n")
                    classes = "../data/animal-classes.names";

                system("./yolo-mark ../data/animal-images ../data/train.txt ../data/animal-classes.names");
                break;

            case 4:
                cout << "Data directory (default = ../darkent/data/animal-images): " << endl;
                getline(cin, data);

                if(data == "\n")
                    data = "../data/animal-images";

                cout << "Training file (default = ../data/train.txt): " << endl;
                getline(cin, train);

                if(train == "\n")
                    train = "../data/train.txt";

                cout << "Training file (default = ../data/animal-classes.names): " << endl;
                getline(cin, classes);

                if(classes == "\n")
                    classes = "../data/animal-classes.names";

                cout << "Writing all image names into data/train.txt..." << endl;

                chdir("..");
                system("find data/animal-images -name \\*.jpg > data/train.txt");
                system("./darknet detector train cfg/animals.data cfg/animals.cfg darknet19_448.conv.23");
                chdir("training");
                break;

            default:
                cout << "Invalid option... try again." << endl;
                break;
        }

        printMenu();
        cin >> choice;
    }

    return 1;
}