#include "filereader.h"
#include <iostream>

bool uniqueChars(std::string substr);

const uint8_t CHARS_IN_PACKET = 4;
const uint8_t CHARS_IN_MESSAGE = 14;

int main () {

  // Create a file reader to read the file in from the input
  std::string line;
  FileReader fr = FileReader("input.txt");

  // Variables to store the positions of the start-of-packet and start-of-message indexes
  uint32_t startOfPacket = -1;
  uint32_t startOfMessage = -1;

  // If we can't read a line from the file then fail the program
  if (!fr.readLine(&line)) {
    return EXIT_FAILURE;
  }

  // Loop through the line and figure out where the start of the input thingy is

  // Variable to keep track of where we stopped with the start of packet loop
  // We are not going to find 14 unique characters if we haven't found 4 in the string so far
  // So the second loop may continue from this point.
  int finalMarker = 0;

  // Iterate through all substrings of length 4 until we find one with all unique characters
  for (int marker = 0; marker < line.length() - CHARS_IN_PACKET; marker++) {
    // Calculate the substring of the last 4 characters before the marker
    if (uniqueChars(line.substr(marker, CHARS_IN_PACKET))) {
      startOfPacket = marker + CHARS_IN_PACKET;
      finalMarker = marker;
      break;
    }
  }

  // Iterate through all substrings of length 14 until we find one with all unique characters
  for (int marker = finalMarker; marker < line.length() - CHARS_IN_MESSAGE; marker++) {
    if (uniqueChars(line.substr(marker, CHARS_IN_MESSAGE))) {
      startOfMessage = marker + CHARS_IN_MESSAGE;
      finalMarker = marker;
      break;
    }
  }

  std::cout << "First start-of-packet marker detected at position " << startOfPacket << std::endl;
  std::cout << "First start-of-message marker detected at position " << startOfMessage << std::endl;

  return EXIT_SUCCESS;
}

bool uniqueChars(std::string substr) {
  // Loop through all of the characters and compare it to the rest of characters in the substring
  for (int first = 0; first < substr.length() - 1; first++) {
    for (int second = first + 1; second < substr.length(); second++) {
      
      // If we find a repeated character then just exit out of the function
      if (substr.at(first) == substr.at(second)) return false;

    }
  }

  return true;
}

