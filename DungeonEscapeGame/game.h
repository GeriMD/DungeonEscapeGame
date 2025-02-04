void startingMessages();

void explanationsMessages();

void readPlayerBoard(const char* filePath);

void printMatrix();

unsigned myStrlen(const char* str);

void myStrcpy(const char* source, char* dest);

void myStrcat(char* first, const char* second);

bool playerFound(char* name, char* playersName);

int returnPlayerLevel(char* playersName);

void addNewPlayer(char* playersName);

void getSize();

void createPlayerBoard(int toOpen);

bool isWall();

bool isKey();

bool isCoin();

bool isPortal();

bool isChest();

bool isBlankSpace();

void movePlayer(char* playersName);

void makeMove(int row, int col);

void checkBoard(char* playersName);

bool isValidLevel();

void findPlayer();

void findPortal();

void start(char* playersName);

bool hasProgress(char* playersName);

void saveProgress(char* playersName);

void readProgress(char* playersName);

void begining(char* playersName);

void readPlayersSavedMatrix(char* playersName);

void saveMap(char* playersName);

void chooseStartingMap(char* playersName);

void winGame(char* playersName);

void gameOver(char* playersName);


