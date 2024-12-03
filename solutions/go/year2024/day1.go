package day1

import (
	"bufio"
	"log"
	"slices"
	"sort"
	"strconv"
	"strings"
)

const estimatedInputLength uint16 = 1 << 10

func SolvePart1(input string) uint32 {
  var totalDistance uint32 = 0
  leftLocs := make([]uint32, 0, estimatedInputLength)
  rightLocs := make([]uint32, 0, estimatedInputLength)
  scanner := bufio.NewScanner(strings.NewReader(input))
  for scanner.Scan() {
    words := strings.Fields(scanner.Text())
    left, lerr := strconv.ParseUint(words[0], 10, 32)
    right, rerr := strconv.ParseUint(words[1], 10, 32)
    if lerr != nil || rerr != nil {
      log.Fatal(lerr, rerr)
    }
    leftLocs = append(leftLocs, uint32(left))
    rightLocs = append(rightLocs, uint32(right))
  }
  if err := scanner.Err(); err!= nil {
    panic("scanner produced an error")
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
    totalDistance += uint32(distance)
  }
  return totalDistance
}

func SolvePart2(input string) uint32 {
  var similarityScore uint32 = 0
  leftLocs := make([]uint32, 0, estimatedInputLength)
  rightLocs := make([]uint32, 0, estimatedInputLength)
  scanner := bufio.NewScanner(strings.NewReader(input))
  for scanner.Scan() {
    words := strings.Fields(scanner.Text())
    left, lerr := strconv.ParseUint(words[0], 10, 32)
    right, rerr := strconv.ParseUint(words[1], 10, 32)
    if lerr != nil || rerr != nil {
      log.Fatal(lerr, rerr)
    }
    leftLocs = append(leftLocs, uint32(left))
    rightLocs = append(rightLocs, uint32(right))
  }
  if err := scanner.Err(); err!= nil {
    panic("scanner produced an error")
  }
  if len(leftLocs) != len(rightLocs) {
    panic("mismatching length of location lists")
  }
  slices.Sort(leftLocs)
  slices.Sort(rightLocs)
  // foreach left number, find amnt of matches in right list and multiply this
  for _, leftLoc := range leftLocs {
    idxRight := sort.Search(
      len(rightLocs),
      func(i int) bool {return rightLocs[i] >= leftLoc},
    )
    if idxRight < len(rightLocs) && rightLocs[idxRight] == leftLoc {
      for rightLocs[idxRight] == leftLoc {
        similarityScore += leftLoc
        idxRight += 1
      }
    }
  }
  return similarityScore
}
