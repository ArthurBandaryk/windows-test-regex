#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(RegexTest, TestDeathOutput) {
  auto operation1 = []() {
    std::cerr << "program: Failed while parsing and validating flags:"
              << std::endl
              << std::endl;

    std::cerr << "* 'bar' must be true" << std::endl;
    std::cerr << "* 'baz' must be greater than 42 " << std::endl;
    exit(1);
  };

  auto operation2 = []() {
    std::cerr << "abc" << std::endl
              << std::endl;
    std::cerr << "abc" << std::endl;
    exit(1);
  };
  
  auto operation3 = []() {
    std::cerr << "Usage: program [...]" << std::endl << std::endl;
    std::cerr << "--[no-]bar help" << std::endl;
    std::cerr << "--baz=... help" << std::endl;
    std::cerr << "-duration=... help" << std::endl;
    std::cerr << "--foo=... help" << std::endl;
    std::cerr << "--[no-]help whether or not to display this help message" << std::endl;
    exit(1);
  };

  const std::string match_regex1 =
      "program: Failed while parsing and validating flags:"
      "\?\n\?\n"
      ". 'bar' must be true"
      "\?\n\?\n"
      ". 'baz' must be greater than 42";

  const std::string match_regex2 = "abc\?\n\?\nabc";
  
  const std::string match_regex3 =
      "Usage: program \\[\\.\\.\\.\\]"
      "\?\n\?\n"
      "--\\[no-\\]bar help\?\n"
      "--baz=\\.\\.\\. help\?\n"
      "--duration=\\.\\.\\. help\?\n"
      "--foo=\\.\\.\\. help\?\n"
      "--\\[no-\\]help whether or not to display this help message";

  EXPECT_DEATH(
      operation1(),
      testing::ContainsRegex(match_regex1));

  EXPECT_DEATH(
      operation2(),
      testing::ContainsRegex(match_regex2));
  
   EXPECT_DEATH(
      operation3(),
      testing::ContainsRegex(match_regex3));
}
