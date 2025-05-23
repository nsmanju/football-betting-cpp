```
# football-betting-cpp
This program implements a simple football match simulation and betting system in C++. It begins by including standard headers for input/output, vectors, strings, and
random number generation, which are essential for handling user interaction, storing teams goals, wager values and simulating match randomness.

The `Team` structure models a football team, storing its name, attack and defense strengths, and accumulated points. It includes a constructor for easy initialization.
The `Bet` structure represents a bet placed on a match, holding pointers to the home and away teams, the simulated scores, the odds for the bet, and the stake
(amount wagered). Its constructor initializes these values.

The `simulateMatch` function simulates a football match between two teams. It uses random number generation to create five scoring opportunities for each team. For each chance,
if the random value exceeds the opposing team's defense strength, a goal is scored. This approach loosely models the influence of defense on match outcomes.

In the `main` function, three teams are created and stored in a vector. A bet is placed on a match between the first two teams with specified odds and stake.
The match is simulated, and the result is printed. If the home team scores more goals, the bet is considered won, and the winnings are calculated and displayed;
otherwise, the stake is lost. This code demonstrates basic object-oriented design, random simulation, and simple betting logic.

This function, `simulateMatch`, models a football match between two teams and returns the number of goals scored by each as a `pair<int, int>`. It takes two
`Team` references—`home` and `away`—and uses random number generation to simulate the unpredictability of a real match. At the start, it initializes a random number generator
 and a uniform distribution that produces floating-point numbers between 0.0 and 1.0. The function then sets both teams' goal counters to zero and defines a constant, `CHANCES`,
 representing the number of scoring opportunities each team gets (five in this case).

For each chance, the function generates two random numbers for each team. A goal is scored by the home team if the first random number is less than the home team's attack
 strength and the second is greater than the away team's defense strength. The same logic applies for the away team, using its attack and the home team's defense.
This approach means that higher attack strengths and lower opposing defense strengths increase the likelihood of scoring.

After all chances are processed, the function returns the final goal counts as a pair, with the first element representing home goals and the second representing away goals.
This design provides a simple but effective way to simulate match outcomes based on team attributes and randomness.

The code segment that is responsible for setting up a bet on a football match between two randomly selected teams picks from a list of teams. First, it defines the betting odds (`2.5`)
and the stake amount (`100.0`). To ensure the match is between two different teams, it uses a uniform integer distribution to randomly pick indices from the `teams` vector.
The variable `home_idx` is assigned a random index, and then a `do-while` loop is used to select `away_idx`, repeating the selection until it is different from `home_idx`.
This guarantees that the home and away teams are not the same.

Once two distinct teams are chosen, a `Bet` object is created using these teams, along with the specified odds and stake. The `Bet` constructor initializes the bet with
the selected teams as home and away, and sets the initial goal counts to zero. This approach adds variety to the simulation by ensuring each bet involves a random matchup,
rather than always using the same teams.

This code snippet generates random values for betting odds and stake amounts, simulating the variability found in real-world betting scenarios. First, it calls the
 `randomDouble` function to produce a random floating-point number between 0.0 and 5.0, representing the raw odds for a bet. To make the odds more realistic and user-friendly,
it rounds this value to one decimal place using `std::round(raw_odds * 10.0) / 10.0`.

Next, the code defines a vector of possible stake amounts, ranging from 10 to 100 in increments of 10. It then uses a uniform integer distribution to randomly select
an index from this vector, ensuring each stake value has an equal chance of being chosen. The selected stake is assigned to the `stake` variable. This approach introduces
 randomness and variety into both the odds and the stake for each simulated bet.


This function, `generateOdds`, is a static utility designed to produce a random betting odds value. It takes a reference to a Mersenne Twister random number generator (`mt19937& gen`)
as its parameter. Inside the function, it calls `randomDouble(0.0, 5.0, gen)` to generate a random floating-point number between 0.0 and 5.0, representing the raw odds.

To make the odds more realistic and easier to display, the function rounds the raw value to one decimal place. This is achieved by multiplying the raw odds by 10, rounding
 the result to the nearest integer, and then dividing by 10.0. The final value is returned as the generated odds. This approach ensures that the odds are both random
 and formatted in a way that is typical for betting scenarios.

***Here are some outcomes from the football betting program***


Odds: 4.0, Stake: $10.0
Goa Warriors (Attack: 0.47, Defense: 0.61)
Bengal Tigers (Attack: 0.68, Defense: 0.65)
Home: Goa Warriors
Away: Bengal Tigers
Match Result: Goa Warriors 0 - 2 Bengal Tigers

You lost the bet. Stake lost: $10.00

Odds: 3.5, Stake: $70.0
Bengal Tigers (Attack: 0.78, Defense: 0.77)
Bengaluru Blues (Attack: 0.59, Defense: 0.86)
Home: Bengal Tigers
Away: Bengaluru Blues
Match Result: Bengal Tigers 0 - 2 Bengaluru Blues
You lost the bet. Stake lost: $70.00


Odds: 4.0, Stake: $10.0
Goa Warriors (Attack: 0.47, Defense: 0.61)
Bengal Tigers (Attack: 0.68, Defense: 0.65)
Home: Goa Warriors
Away: Bengal Tigers
Match Result: Goa Warriors 0 - 2 Bengal Tigers
You lost the bet. Stake lost: $10.00

Odds: 3.5, Stake: $70.0
Bengal Tigers (Attack: 0.78, Defense: 0.77)
Bengaluru Blues (Attack: 0.59, Defense: 0.86)
Home: Bengal Tigers
Away: Bengaluru Blues
Match Result: Bengal Tigers 0 - 2 Bengaluru Blues
You lost the bet. Stake lost: $70.00

Odds: 4.8, Stake: $100.0
Bengaluru Blues (Attack: 0.79, Defense: 0.63)
Goa Warriors (Attack: 0.41, Defense: 0.87)
Home: Bengaluru Blues
Away: Goa Warriors
Match Result: Bengaluru Blues 3 - 1 Goa Warriors
You won the bet! Winnings: $480.00

nadkalpur@nadkalpur-Lenovo-S510:~/Documents/elementary_football$ ./football_wager_rnd_copy
Odds: 4.4, Stake: $60.0
Kerala Blasters (Attack: 0.54, Defense: 0.78)
Goa Warriors (Attack: 0.71, Defense: 0.77)
Home: Kerala Blasters
Away: Goa Warriors
Match Result: Kerala Blasters 1 - 0 Goa Warriors
You won the bet! Winnings: $264.00
```
