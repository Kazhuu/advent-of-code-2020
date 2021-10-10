#include <vector>
#include <string>
#include <deque>
#include <iostream>
#include <cassert>

std::pair<std::deque<int64_t>, std::deque<int64_t>> parse_input() {
    std::deque<int64_t> player1;
    std::deque<int64_t> player2;
    std::string line;
    std::getline(std::cin, line);
    while(std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        player1.emplace_back(std::stoi(line));
    }
    std::getline(std::cin, line);
    while(std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        player2.emplace_back(std::stoi(line));
    }
    return std::make_pair(player1, player2);
}

void print_deck(const std::deque<int64_t> &deck) {
    std::cout << "Deck: ";
    for (auto card : deck) {
        std::cout << card << " ";
    }
    std::cout << std::endl;
}

void play_turn(std::deque<int64_t> &player1, std::deque<int64_t> &player2) {
    int64_t player1_card = player1.front();
    int64_t player2_card = player2.front();
    player1.pop_front();
    player2.pop_front();
    if (player1_card > player2_card) {
        player1.push_back(player1_card);
        player1.push_back(player2_card);
        std::cout << "Player 1 wins!" << std::endl;
    } else if (player2_card > player1_card) {
        player2.push_back(player2_card);
        player2.push_back(player1_card);
        std::cout << "Player 2 wins!" << std::endl;
    } else {
        std::cout << "draw" << std::endl;
    }
}

uint64_t calculate_points(const std::deque<int64_t> &deck) {
    uint64_t total = 0;
    for (int64_t i = 0; i < deck.size(); ++i) {
        total += deck[i] * (deck.size() - i);
    }
    return total;
}

int main() {
    auto [player1, player2] = parse_input();
    int64_t turn = 1;
    while (player1.size() != 0 && player2.size() != 0) {
        std::cout << "Turn " << turn << std::endl;
        std::cout << "Player 1 ";
        print_deck(player1);
        std::cout << "Player 2 ";
        print_deck(player2);
        play_turn(player1, player2);
        ++turn;
    }
    uint64_t score = 0;
    if (player1.empty()) {
        score = calculate_points(player2);
    } else if (player2.empty()) {
        score = calculate_points(player1);
    } else {
        assert(false && "no winner");
    }
    std::cout << "first answer: " << score << std::endl;
    assert(score == 36257 && "first solution doesn't match");
    return 0;
}
