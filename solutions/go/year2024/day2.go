package year2024

import (
	"bufio"
	"strconv"
	"strings"
)

func SolveDay2Part1(input string) uint32 {
  var safeReportsAmnt uint32 = 0
  scanner := bufio.NewScanner(strings.NewReader(input))
  lineScanner:
  for scanner.Scan() {
    levels := strings.Fields(scanner.Text())
    var isInc bool = false
    var prevLevel int8 = 0
    for i, levelStr := range levels {
      levelParsed, err := strconv.ParseInt(levelStr, 10, 8)
      if err != nil {
        panic("error converting level from string to uint8")
      }
      curLevel := int8(levelParsed)
      if i == 0 {
        prevLevel = curLevel
        continue
      }
      if i == 1 {
        isInc = curLevel > prevLevel
      }
      if curLevel == prevLevel {
        continue lineScanner
      }
      if isInc != (curLevel > prevLevel) {
        continue lineScanner
      }
      levelDelta := curLevel - prevLevel
      if levelDelta < -3 || levelDelta > 3 {
        continue lineScanner
      }
      prevLevel = curLevel
    }
    safeReportsAmnt += 1
  }
  if err := scanner.Err(); err!= nil {
    panic("scanner produced an error")
  }
  return safeReportsAmnt
}

func SolveDay2Part2(input string) uint32 {
  return 42
}
