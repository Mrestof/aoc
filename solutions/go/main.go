package main

import (
	"fmt"
	"log"
	"mrestof/aoc/year2024"
	"os"
)

func main() {
  // TODO: move out to a separate input retreiver function
  content, err := os.ReadFile(
    "/home/mrestof/docs/dev/study/practice/aoc/me/inputs/2024_1.txt",
  )
  if err != nil {
    log.Fatal(err)
  }
  answer1 := day1.SolvePart1(string(content))
  answer2 := day1.SolvePart2(string(content))
  fmt.Println("Answer for year 2024 day 1 part 1:", answer1)
  fmt.Println("Answer for year 2024 day 1 part 2:", answer2)
}
