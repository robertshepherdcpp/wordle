#include<iostream> // std::cout
#include<vector>   // std::vector
#include<string>   // std::string
#include<fstream>  // std::ifstream
#include<random>   // random things
#include<fstream>  // std::ofstream

auto has(std::string s, char c) -> bool
{
    for (auto x : s)
    {
        if (x == c) { return true; }
    }
    return false;
}

auto compare(std::string maybe, std::string to_compare, std::vector<char>& vec) -> std::string
{
    std::string result{};
    for (int i = 0; i < to_compare.size() && i < maybe.size(); i++)
    {
        if (maybe[i] == to_compare[i])
        {
            result += "#";
            vec.push_back('🟩');
        }
        else if (has(to_compare, maybe[i]))
        {
            result += "~";
            vec.push_back('🟨');
        }
        else
        {
            vec.push_back('⬛');
            result += "-";
        }
    }
    return result;
}

int main()
{
    // read in from the file into a vector
    std::string line{};
    std::vector<std::string> vec{};
    std::ifstream myfile("words.txt");
    std::vector<char> results_table{};
    if (myfile.is_open())
    {
        while (std::getline(myfile, line))
        {
            vec.push_back(line);
        }
        myfile.close();
    }

    // get the random number
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1005); // distribution in range [1, 6]
    auto random_number = dist6(rng);

    std::string random_word = vec[random_number];
    std::string input{};

    // now do the wordle part of it;

    int number_of_goes = 0;
    while (number_of_goes < 6 && input != random_word)
    {
        std::cin >> input;
        std::string s = compare(input, random_word, results_table);
        std::cout << "\n\n\n\n\n\n\n\n\n";
        for (auto x : input)
        {
            std::cout << x << "    ";
        }
        std::cout << "\n";
        for (auto x : s)
        {
            std::cout << x << "    ";
        }
        std::cout << "\n\n\n\n\n\n\n\n\n";
        number_of_goes += 1;
    }
    std::cout << "The answer was: " << random_word << "\n";

    for (int i = 0; i < results_table.size(); i++)
    {
        std::cout << results_table[i];
        if (i % 5 == 0)
        {
            std::cout << "\n";
        }
    }

    std::ofstream file_result("emoji_file.txt");
    file_result << results_table.data();
}