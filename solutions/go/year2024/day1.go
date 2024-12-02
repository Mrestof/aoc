package day1

import (
	"bufio"
	"log"
	"slices"
	"strconv"
	"strings"
)

const estimatedInputLength uint16 = 1 << 10

func SolvePart1(input bufio.Scanner) uint32 {
  var totalDistance uint32 = 0
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
  if len(leftLocs) != len(rightLocs) {
    panic("mismatching length of location lists")
  }
  slices.Sort(leftLocs)
  slices.Sort(rightLocs)
  for i := 0; i < len(leftLocs); i++ {
    var distance int16 = int16(leftLocs[i] - rightLocs[i])
    if distance < 0 {
      distance = -distance
    }
    println(leftLocs[i], rightLocs[i], distance)
    totalDistance += uint32(distance)
  }
  return totalDistance
}
