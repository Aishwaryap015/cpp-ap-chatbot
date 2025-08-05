#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include "io.h"

std::map<std::string, std::string> learned_responses;

// Load learned responses from file
void load_learned_responses() {
    std::ifstream infile("learned.txt");
    std::string key, value;
    while (std::getline(infile, key) && std::getline(infile, value)) {
        learned_responses[key] = value;
    }
}

// Save new input-response pair to file
void save_learned_response(const std::string& input, const std::string& reply) {
    std::ofstream outfile("learned.txt", std::ios::app);
    if (!outfile) {
        print_c("Error: Could not open learned.txt to save.\n");
        return;
    }
    outfile << input << "\n" << reply << "\n";
    learned_responses[input] = reply;
}

// Normalize user input (lowercase + remove unwanted chars)
std::string normalize(const std::string& str) {
    std::string out;
    for (char c : str) {
        if (isalpha(c) || isspace(c))
            out += tolower(c);
    }
    return out;
}

// Get response
std::string get_response(const std::string& input) {
    std::string in = normalize(input);

    if (in.empty())
        return "Please say something.";

    // Predefined replies
    if (in.find("hello") != std::string::npos || in.find("hi") != std::string::npos)
        return "Hi there!";
    else if (in.find("how are you") != std::string::npos)
        return "I'm learning new things every day!";
    else if (in.find("your name") != std::string::npos)
        return "I'm ChatBot-C++, your learning assistant!";
    else if (in.find("what can you do") != std::string::npos)
        return "I can:\n- Greet you\n- Learn new things\n- Save conversations\n- Talk simply\n- Exit on 'bye'";
    else if (in.find("bye") != std::string::npos)
        return "Goodbye! Talk to you soon.";

    // Learned responses
    auto it = learned_responses.find(in);
    if (it != learned_responses.end())
        return it->second;

    // Ask user to teach
    std::string new_response;
    print_c("I don't know how to respond. What should I say?\nYou: ");
    std::getline(std::cin, new_response);
    save_learned_response(in, new_response);
    return new_response;
}

// Main function
int main() {
    print_c("Hi there! 👋 I’m ChatBot-C++\n");
    print_c("Here’s what I can do:\n");
    print_c(" - Greet you when you say hi or hello\n");
    print_c(" - Respond to simple questions like 'how are you?'\n");
    print_c(" - Learn new responses and remember them\n");
    print_c(" - Exit when you type 'bye'\n\n");

    load_learned_responses();

    std::string user_input;
    while (true) {
        std::cout << "You: ";
        std::getline(std::cin, user_input);

        if (user_input.empty())
            continue;

        std::string response = get_response(user_input);
        print_c(("Bot: " + response + "\n").c_str());

        if (normalize(user_input).find("bye") != std::string::npos)
            break;
    }

    return 0;
}
