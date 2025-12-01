package main

import (
	"fmt"
	"log"
	"mrestof/aoc/year2024"
	"mrestof/aoc/types"
	"os"
)

func findInputs() string {
  // TODO: implement backward search or other method of getting a path
  return "/home/mrestof/docs/dev/study/practice/aoc/me/inputs/"
}

func runYear(year uint16) {
  var solutions types.DTSolutions
  switch year {
  case 2024:
    solutions = year2024.Solutions
  default:
    panic("unavailable year selected")
  }
  for i := 0; i < len(solutions); i += 2 {
    day := i/2 + 1
    inputFileName := fmt.Sprintf("%d_%d.txt", year, day)
    content, err := os.ReadFile(
      findInputs() + inputFileName,
    )
    if err != nil {
      log.Fatalf(
        "%q not found, make sure to get it to the 'inputs' folder",
        inputFileName,
      )
    }
    answer1 := solutions[i](string(content))
    fmt.Printf("Answer for year 2024 day %d part 1: %d\n", day, answer1)
    if i+1 < len(solutions) {
      answer2 := solutions[i+1](string(content))
      fmt.Printf("Answer for year 2024 day %d part 2: %d\n", day, answer2)
    }
  }
}

func main() {
  runYear(2024)
  //levels := []int{1, 2, 3, 4}
  //fmt.Printf("levels %d\n", levels)
  //fmt.Printf(":1 %d\n", levels[:1])
  //fmt.Printf("2: %d\n", levels[2:])
  //fmt.Printf(":2 %d\n", levels[:2])
  //fmt.Printf("3: %d\n", levels[3:])
  //fmt.Printf(":1+2: %d\n", append(levels[:1], levels[2:]...))
  //fmt.Printf("levels %d\n", levels)
  //fmt.Printf(":2+3: %d\n", append(levels[:2], levels[3:]...))
  //fmt.Printf("levels %d\n", levels)
}
