/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test {
protected:
    Guesser* guesser;

    GuesserTest() : guesser(nullptr) {} // Constructor runs before each test
    virtual ~GuesserTest() { delete guesser; } // Destructor cleans up after tests
    virtual void SetUp() {} // Sets up before each test
    virtual void TearDown() { delete guesser; guesser = nullptr; } // Clean up after each test
};

// /* Example test
// TEST(GuesserTest, smoke_test)
// {
//     ASSERT_EQ( 1+1, 2 );
// }
// */

TEST_F(GuesserTest, GuessLengthTesting) {
    guesser = new Guesser("ThisIsAVeryLongSecretStringThatExceeds32Characters");
    EXPECT_EQ(guesser->remaining(), 3); //Check guesses start at 3
}

TEST_F(GuesserTest, ExhaustGuessAndCheckMatch) {
    guesser = new Guesser("apple");

    EXPECT_FALSE(guesser->match("applz")); //One char different, does not match
    EXPECT_EQ(guesser->remaining(), 2); //Remaining guesses decrements

    EXPECT_FALSE(guesser->match("applz")); //One char different again
    EXPECT_EQ(guesser->remaining(), 1); //remaining guesses decrements

    EXPECT_FALSE(guesser->match("applz")); //Third attempt, still not matching
    EXPECT_EQ(guesser->remaining(), 0); //Remaining guesses decrement

    EXPECT_FALSE(guesser->match("apple")); //No remaining guesses, even though it matches secret
}

TEST_F(GuesserTest, CorrectGuessTest) {
    guesser = new Guesser("aditya");
    EXPECT_TRUE(guesser->match("aditya")); // Correct guess
}

TEST_F(GuesserTest, DistanceMoreThanTwoLocksSecret) {
    guesser = new Guesser("cat");

    EXPECT_FALSE(guesser->match("dog")); //locks guess
    EXPECT_FALSE(guesser->match("cat")); //cannot proceed even if guess is right
}

TEST_F(GuesserTest, NonAlphabetSecret) {
	guesser = new Guesser("%__&7");
	EXPECT_FALSE(guesser->match("%__&6"));
	EXPECT_EQ(guesser->remaining(),2);
	EXPECT_TRUE(guesser->match("%__&7"));
}

TEST_F(GuesserTest, LargeLengthDifference) {
    guesser = new Guesser("short"); //Secret of length 5

    EXPECT_EQ(guesser->match("veryverylong"), false); // Distance triggers line 24's return
}

TEST_F(GuesserTest, TotalDistanceExceedsSecretLength) {
    guesser = new Guesser("abcd"); // Secret of length 4

    EXPECT_FALSE(guesser->match("abcdefghij")); // Match checks `tDistance`
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
