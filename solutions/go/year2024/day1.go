package day1

import (
	"bufio"
	"log"
	"strconv"
	"strings"
)

const estimatedInputLength = 10_000

func Solve1(input bufio.Scanner) uint32 {
  leftLocs := make([]uint32, 0, estimatedInputLength)
  rightLocs := make([]uint32, 0, estimatedInputLength)
  for input.Scan() {
    words := strings.Fields(input.Text())
    left, lerr := strconv.ParseUint(words[0], 10, 32)
    right, rerr := strconv.ParseUint(words[1], 10, 32)
    if lerr != nil || rerr != nil {
      log.Fatal(lerr, rerr)
    }
    leftLocs = append(leftLocs, uint32(left))
    rightLocs = append(rightLocs, uint32(right))
  }
  // sort each loc list
  // calculate distance for each loc pair
  return 42
}
