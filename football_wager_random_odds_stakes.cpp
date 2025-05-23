/* This program implements a simple football match simulation and betting system in C++. It begins by including 
standard headers for input/output, vectors, strings, and random number generation, which are essential for handling
 user interaction, storing teams goals, wager values and simulating match randomness.

The `Team` structure models a football team, storing its name, attack and defense strengths, and accumulated points. 
It includes a constructor for easy initialization. The `Bet` structure represents a bet placed on a match, 
holding pointers to the home and away teams, the simulated scores, the odds for the bet, and the stake (amount wagered).
 Its constructor initializes these values.

The `simulateMatch` function simulates a football match between two teams. It uses random number generation 
to create five scoring opportunities for each team. For each chance, if the random value exceeds
 the opposing team's defense strength, a goal is scored. 
 This strategy loosely models the influence of defense on match outcomes.
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::mt19937;
using std::pair;
using std::random_device;
using std::setprecision;
using std::string;
using std::uniform_real_distribution;
using std::vector;

// Helper function to round a double to two decimal places
double round2(double value) { return std::round(value * 100.0) / 100.0; }

// Structure to represent a football team
struct Team {
  string name;
  double attack_strength;  // scale 0-1
  double defense_strength; // scale 0-1
  int points;

  Team(string n, double atk, double def)
      : name(n), attack_strength(round2(atk)), defense_strength(round2(def)),
        points(0) {}
};

// Structure to represent a bet on a match
struct Bet {
  Team home_team;
  Team away_team;
  int home_goals;
  int away_goals;
  double odds;
  double stake;

  Bet(Team h, Team a, double o, double s)
      : home_team(h), away_team(a), home_goals(0), away_goals(0), odds(o),
        stake(s) {}
};

// Generates a random double in [min, max]
double randomDouble(double min, double max, mt19937 &gen) {
  uniform_real_distribution<> dis(min, max);
  return dis(gen);
}

// Simulates a match and returns goals scored by each team
pair<int, int> simulateMatch(Team &home, Team &away, mt19937 &gen) {
  uniform_real_distribution<> dis(0.0, 1.0);

  int home_goals = 0, away_goals = 0;
  const int CHANCES = 10;

  for (int i = 0; i < CHANCES; ++i) {
    if (dis(gen) < home.attack_strength && dis(gen) > away.defense_strength) {
      home_goals++;
    }
    if (dis(gen) < away.attack_strength && dis(gen) > home.defense_strength) {
      away_goals++;
    }
  }

  return {home_goals, away_goals};
}


/* In the `main` function, three teams are created and stored in a vector. A bet is placed on a match 
between the first two teams with specified odds and stake. The match is simulated, and the result is printed. 
If the home team scores more goals, the bet is considered won, and the winnings are calculated and displayed; 
otherwise, the stake is lost. This code demonstrates basic object-oriented design, random simulation, and 
simple betting logic. */

int main() {
  random_device rd;
  mt19937 gen(rd());

  // Create teams with random strengths in attack and defense
  vector<Team> teams;
  teams.emplace_back("Bengaluru Blues", randomDouble(0.4, 0.9, gen),
                     randomDouble(0.4, 0.9, gen));
  teams.emplace_back("Kerala Blasters", randomDouble(0.4, 0.9, gen),
                     randomDouble(0.4, 0.9, gen));
  teams.emplace_back("Bengal Tigers", randomDouble(0.4, 0.9, gen),
                     randomDouble(0.4, 0.9, gen));
  teams.emplace_back("Goa Warriors", randomDouble(0.4, 0.9, gen),
                     randomDouble(0.4, 0.9, gen));

  // Define a structure to encapsulate betting logic
  struct BettingSystem {
    // Generate random odds between 0 and 5, rounded to one decimal place
    static double generateOdds(mt19937 &gen) {
      double raw_odds = randomDouble(0.0, 5.0, gen);
      return std::round(raw_odds * 10.0) / 10.0;
    }

    // Select a random stake from possible values
    static double selectStake(mt19937 &gen) {
      vector<double> stakes = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
      std::uniform_int_distribution<> stake_dist(0, stakes.size() - 1);
      return stakes[stake_dist(gen)];
    }

    // Randomly select two different teams for a match
    static pair<int, int> selectTeams(const vector<Team> &teams, mt19937 &gen) {
      std::uniform_int_distribution<> team_dist(0, teams.size() - 1);
      int home_idx = team_dist(gen);
      int away_idx;
      do {
        away_idx = team_dist(gen);
      } while (away_idx == home_idx);
      return {home_idx, away_idx};
    }

    // Place a bet by selecting teams, odds, and stake
    static Bet placeBet(const vector<Team> &teams, mt19937 &gen) {
      auto team_indices = selectTeams(teams, gen);
      double odds = generateOdds(gen);
      double stake = selectStake(gen);
      return Bet(teams[team_indices.first], teams[team_indices.second], odds,
                 stake);
    }
  };

  // Place a bet using the BettingSystem structure
  Bet bet = BettingSystem::placeBet(teams, gen);

  // Print odds and stake
  cout << "Odds: " << fixed << setprecision(1) << bet.odds << ", Stake: $"
       << bet.stake << endl;

  // Simulate the match
  pair<int, int> result = simulateMatch(bet.home_team, bet.away_team, gen);
  bet.home_goals = result.first;
  bet.away_goals = result.second;

  // Display team strengths rounded to two decimal places
  cout << fixed << setprecision(2);
  cout << bet.home_team.name << " (Attack: " << bet.home_team.attack_strength
       << ", Defense: " << bet.home_team.defense_strength << ")\n";
  cout << bet.away_team.name << " (Attack: " << bet.away_team.attack_strength
       << ", Defense: " << bet.away_team.defense_strength << ")\n";

  // Display result
  cout << "Home: " << bet.home_team.name << endl;
  cout << "Away: " << bet.away_team.name << endl;
  cout << "Match Result: " << bet.home_team.name << " " << bet.home_goals
       << " - " << bet.away_goals << " " << bet.away_team.name << endl;

  // Evaluate the bet
  if (bet.home_goals > bet.away_goals) {
    double winnings = bet.stake * bet.odds;
    cout << "You won the bet! Winnings: $" << winnings << endl;
  } else {
    cout << "You lost the bet. Stake lost: $" << bet.stake << endl;
  }

  return 0;
}