class MFVFormat {
  private:
    struct Message {
      char module[32];
      char feature[32];
      char value[32];
    };

  public:
    struct Message message;
    void parse(char command[]);
    int parseValueToInt(int newValue[]);
};

void MFVFormat::parse(char command[]) {
  int i = 0;
  int j = 0;

  // Clear old data
  for (int k = 0; k < 32; k++) {
    message.module[k] = '\0';
    message.feature[k] = '\0';
    message.value[k] = '\0';
  }

  if (command[i] == '@') {
    // Get module
    i++;
    while (command[i] != '|' && command[i] != '$') {
      message.module[j] = command[i];
      i++;
      j++;
    }
    message.module[j] = '\0';

    // Get feature
    j = 0;
    if (command[i] == '|') {
      i++;
      while (command[i] != '$' && command[i] != ';') {
        message.feature[j] = command[i];
        i++;
        j++;
      }
      message.feature[j] = '\0';
    }
    
    // Get value
    j = 0;
    if (command[i] == '$') {
      while (command[i] != ';') {
        message.value[j] = command[i];
        i++;
        j++;
      }
      message.value[j] = '\0';
    }
  }
}

int MFVFormat::parseValueToInt(int newValue[]) {
  char charValue[8][8];

  int i = 0;
  int r = 0;
  int c = 0;

  if (message.value[i] == '$') {
    i++;
  }

  while (message.value[i] != '\0') {
    if (message.value[i] == '$') {
      i++;
      r++;

      c = 0;
    }

    charValue[r][c] = message.value[i];

    i++;
    c++;
  }
  charValue[r][c] = '\0';
  
  // Assign to newValue variable
  for (int j = 0; j <= r; j++) {
    newValue[j] = atoi(charValue[j]);
  }

  // Return number of data
  r++;
  return r;
}
