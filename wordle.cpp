#include<iostream> // std::cout
#include<vector>   // std::vector
#include<string>   // std::string
#include<fstream>  // std::ifstream
#include<random>   // random things

auto has(std::string s, char c) -> bool
{
    for (auto x : s)
    {
        if (x == c) { return true; }
    }
    return false;
}

auto compare(std::string maybe, std::string to_compare) -> std::string
{
    std::string result{};
    for (int i = 0; i < to_compare.size() && i < maybe.size(); i++)
    {
        if (maybe[i] == to_compare[i])
        {
            result += "#";
        }
        else if (has(to_compare, maybe[i]))
        {
            result += "~";
        }
        else
        {
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
        std::string s = compare(input, random_word);
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
    std::cout << "The answer was: " << random_word;
}