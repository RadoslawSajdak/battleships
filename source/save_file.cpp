#include <save_file.h>

void save(Board player_1, Board player_2)
{
    string data_to_save;
    ofstream save_file;
    if (player_1.get_ships_left() > 9 && player_2.get_ships_left() > 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + to_string(player_1.get_ships_left());
    if (player_1.get_ships_left() <= 9 && player_2.get_ships_left() <= 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + "0" + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + "0" + to_string(player_1.get_ships_left());
    else if (player_1.get_ships_left() <= 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + "0" + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + to_string(player_2.get_ships_left());
    else if (player_2.get_ships_left() <= 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + "0" + to_string(player_1.get_ships_left());
    save_file.open("Saves.txt", std::ofstream::trunc);
    save_file << data_to_save;
    save_file.close();
    cout << "Saved game!!" << endl;
}

void load(Board* player_1, Board* player_2)
{
    string load_data, player_data1, player_data2;
    ifstream load_file;

    load_file.open("Saves.txt");
    getline(load_file, load_data);
    load_file.close();

    if (load_data.size() > 10)
    {
        int loaded_len = 0;
        for (int i = 0; i < 164; i++)
        {
            player_data1 += load_data[loaded_len];
            loaded_len++;
        }
        cout << "Loaded: " << loaded_len << endl;
        for (int j = 0; j < 164; j++)
        {
            player_data2 += load_data[loaded_len];;
            loaded_len++;
        }
        cout << "Loaded: " << loaded_len << endl;

        player_1->load_boards(player_data1);
        player_2->load_boards(player_data2);
    }
    else
    {
        cout << "There's no save data! Starting a new game!" << endl;
        Sleep(2000);
    }
}