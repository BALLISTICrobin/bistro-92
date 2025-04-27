#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON1_PIN 4  // Menu/Reset
#define BUTTON2_PIN 5  // Select/Submit
#define BUTTON3_PIN 18 // Scroll Up/Increment
#define BUTTON4_PIN 19 // Scroll Down/Decrement

String menuItems[] = {"Burger", "Pizza", "Pasta"};
int menuCount = 3;
int currentItem = 0;
int quantity = 1;
bool inMenu = true;
bool inQuantity = false;
String cart = "";
unsigned long button2PressTime = 0;
bool button2Pressed = false;

void setup() {
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  showMenu();
}

void loop() {
  // Button 1: Reset or open menu
  if (digitalRead(BUTTON1_PIN) == LOW) {
    inMenu = true;
    inQuantity = false;
    currentItem = 0;
    quantity = 1;
    cart = "";
    showMenu();
    delay(200);
  }

  // Button 3: Scroll up or increment quantity
  if (digitalRead(BUTTON3_PIN) == LOW) {
    if (inMenu) {
      currentItem = (currentItem + 1) % menuCount;
      showMenu();
    } else if (inQuantity) {
      quantity++;
      showQuantity();
    }
    delay(200);
  }

  // Button 4: Scroll down or decrement quantity
  if (digitalRead(BUTTON4_PIN) == LOW) {
    if (inMenu) {
      currentItem = (currentItem - 1 + menuCount) % menuCount;
      showMenu();
    } else if (inQuantity) {
      quantity = max(1, quantity - 1);
      showQuantity();
    }
    delay(200);
  }

  // Button 2: Select item, confirm quantity, or submit order
  if (digitalRead(BUTTON2_PIN) == LOW && !button2Pressed) {
    button2Pressed = true;
    button2PressTime = millis();
  }
  if (digitalRead(BUTTON2_PIN) == HIGH && button2Pressed) {
    button2Pressed = false;
    unsigned long pressDuration = millis() - button2PressTime;
    if (pressDuration >= 1000) { // Long press (>= 1 second)
      if (cart != "") {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Order Sent!");
        display.display();
        Serial.println("Order Submitted: Table 1, " + cart);
        cart = "";
        delay(2000);
      } else {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("No Items in Cart");
        display.display();
        delay(2000);
      }
      inMenu = true;
      inQuantity = false;
      currentItem = 0;
      quantity = 1;
      showMenu();
    } else { // Short press
      if (inMenu) {
        inMenu = false;
        inQuantity = true;
        showQuantity();
      } else if (inQuantity) {
        inMenu = true;
        inQuantity = false;
        cart += menuItems[currentItem] + " x" + String(quantity) + ", ";
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Added to Cart");
        display.display();
        delay(1000);
        quantity = 1;
        showMenu();
      }
    }
    delay(200);
  }
}

void showMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  for (int i = 0; i < menuCount; i++) {
    display.setTextSize(i == currentItem ? 2 : 1);
    display.print(i == currentItem ? "* " : "  ");
    display.println(menuItems[i]);
  }
  display.setTextSize(1);
  display.setCursor(0, 50); // Place cart at bottom
  String cartDisplay = cart == "" ? "Cart: Empty" : "Cart: " + cart;
  if (cartDisplay.length() > 20) { // Limit to ~20 characters to fit 128px width
    cartDisplay = cartDisplay.substring(0, 17) + "...";
  }
  display.println(cartDisplay);
  display.display();
}

void showQuantity() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Quantity: ");
  display.println(quantity);
  display.display();
}