#include "filereader.h"
#include <iostream>

bool hasNoRepeatedCharacters(std::string line);

int main () {

  // Create a file reader to read the file in from the input
  std::string line;

  FileReader fr = FileReader("input.txt");

  uint32_t startOfPacket = -1;
  uint32_t startOfMessage = -1;

  if (!fr.readLine(&line)) {
    return EXIT_FAILURE;
  }

  std::cout << "Reading input: " << line << std::endl;

  // Loop through the line and figure out where the start of the input thingy is

  int finalMarker = 0;

  for (int marker = 0; marker < line.length() - 4; marker++) {
    // Calculate the substring of the last 4 characters before the marker
    if (hasNoRepeatedCharacters(line.substr(marker, 4))) {
      startOfPacket = marker + 4;
      finalMarker = marker;
      break;
    }
  }

  for (int marker = finalMarker; marker < line.length() - 14; marker++) {
    if (hasNoRepeatedCharacters(line.substr(marker, 14))) {
      startOfMessage = marker + 14;
      finalMarker = marker;
      break;
    }
  }

  std::cout << "First start-of-packet marker detected at position " << startOfPacket << std::endl;
  std::cout << "First start-of-message marker detected at position " << startOfMessage << std::endl;

  return EXIT_SUCCESS;
}

bool hasNoRepeatedCharacters(std::string line) {
  // Loop through all of the characters and compare it to the rest
  for (int first = 0; first < line.length() - 1; first++) {
    for (int second = first + 1; second < line.length(); second++) {

      if (line.at(first) == line.at(second)) return false;

    }
  }

  return true;
}

