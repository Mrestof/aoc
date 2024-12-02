package main

import (
	"bufio"
	"fmt"
	"log"
	"mrestof/aoc/year2024"
	"os"
)

func main() {
  // TODO: move out to a separate input retreiver function
  f, err := os.Open(
    "/home/mrestof/docs/dev/study/practice/aoc/me/inputs/2024_1.txt",
  )
  if err != nil {
    log.Fatal(err)
  }
  defer f.Close()
  scanner := bufio.NewScanner(f)
  answer := day1.SolvePart1(*scanner)
  fmt.Println("Answer for year 2024 day 1:", answer)
}
