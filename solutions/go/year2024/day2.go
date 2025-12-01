package year2024

import (
	"bufio"
	"fmt"
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

func isReportSafe(levels []string, isDumping bool) bool {
  var isInc bool = false
  var prevLevel int8 = 0
  dumpingNeeded := false
  fmt.Printf("begin:%s\n", levels)
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
      dumpingNeeded = true
    }
    if isInc != (curLevel > prevLevel) {
      dumpingNeeded = true
    }
    levelDelta := curLevel - prevLevel
    if levelDelta < -3 || levelDelta > 3 {
      dumpingNeeded = true
    }
    if dumpingNeeded {
      if isDumping {
        print("unsafe\n")
        return false
      }
      // FIX: Try removing every level
      fmt.Printf("start two dumpings\n")
      // this copying stuff looks stupid, but I can't just do
      // "append(levels[:i-1], levels[i:]...)" 2 times in a row,
      // cuz it will fuck up the underlying array...
      dumpedReportv1 := make([]string, len(levels))
      dumpedReportv2 := make([]string, len(levels))
      copy(dumpedReportv1, levels)
      copy(dumpedReportv2, levels)
      dumpedReportv1 = append(dumpedReportv1[:i-1], dumpedReportv1[i:]...)
      dumpedReportv2 = append(dumpedReportv2[:i], dumpedReportv2[i+1:]...)
      switch {
        case isReportSafe(dumpedReportv1, true):
        case isReportSafe(dumpedReportv2, true):
        default:
          print("unsafe\n")
          return false
      }
      print("safe\n")
      return true
    }
    prevLevel = curLevel
  }
  print("safe\n")
  return true
}

func SolveDay2Part2(input string) uint32 {
  var safeReportsAmnt uint32 = 0
  scanner := bufio.NewScanner(strings.NewReader(input))
  i := 0
  for scanner.Scan() {
    println(i)
    levels := strings.Fields(scanner.Text())
    if isReportSafe(levels, false) {
      safeReportsAmnt += 1
    }
    println()
    i++
  }
  if err := scanner.Err(); err!= nil {
    panic("scanner produced an error")
  }
  return safeReportsAmnt
}
