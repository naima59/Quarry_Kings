# 🪨 Quarry Kings (C++ / Raylib)
Quarry Kings is a fast-paced resource clicker game built in C++ using the Raylib rendering library. Your objective: mine 1 million stone as fast as possible. Inspired by classic clicker mechanics, Quarry Kings blends strategic upgrade paths, satisfying feedback loops, and a race-against-the-clock leaderboard system.
Whether you're optimizing your stone-per-second or racing to beat your fastest run, Quarry Kings rewards precision, timing, and upgrade efficiency.

## ⚙️ Project Features
### ⛏️ Four Upgrade Paths:
- Pickaxe Quality
- Villagers
- Oxen
- Cart
Each upgrade boosts your stone production through click or passive generation.
### 🖼️ Visuals & Rendering:
- Built with Raylib for lightweight 2D rendering
- All textures generated via Copilot image tools
- Custom splash screens, victory screens, and upgrade icons
### 🧠 Gameplay Systems:
- Persistent leaderboard tracking top 5 fastest runs
- Comma-formatted stone count for readability
- Victory screen with elapsed time and restart flow
- Modular upgrade logic with scalable cost/output curves
### 🎮 Controls:
- Mouse click to mine stone
- Hover and click upgrade icons to purchase
- Victory triggers at 1,000,000 stone
### 🧹 Code Quality:
- Formatted with clang-format for consistency
- Modular architecture and header hygiene
- Asset cleanup and memory management on unload

## 🎥 Gameplay Previews
### 🏰 Game Intro
The King's decree and your quest to mine 1 million stone begins...
![Game Intro](https://github.com/naima59/Quarry_Kings/blob/main/demo/Quarry_Kings_Intro.gif?raw=true)

### ⛏️ Moment-to-Moment Gameplay
Click, upgrade, and race the clock to build the fortress.
![Gameplay](https://github.com/naima59/Quarry_Kings/blob/main/demo/Quarry_Kings_Gameplay.gif?raw=true)


## 🧭 How to Run the Game
🔹 Option 1: Run the Release Version
- Navigate to the install/ folder
- Double-click QuarryKings.exe
- Start mining and upgrading!

🔹 Option 2: Build from Source (Advanced)
- Clone the repository:
git clone https://github.com/yourusername/QuarryKings.git
- Make sure you have Raylib installed
- Compile the project using your preferred C++ compiler:
g++ src/*.cpp -o QuarryKings -lraylib
- Run the executable:
./QuarryKings

## 📁 Project Structure

<pre>📦 Quarry_Kings/
├── 📁 .git/                 # Git version control data
├── 📁 .vscode/              # VS Code settings and tasks
├── 📁 bin/                  # Compiled binaries (optional use)
├── 📁 demo/                 # Demo assets or test builds
├── 📁 include/              # Header files (.h)
├── 📁 install/              # Release version executable
│   └── QuarryKings.exe
├── 📁 resources/            # Game assets: sprites, sounds, fonts
├── 📁 src/                  # Source code (.cpp)
├── 📄 .gitattributes
├── 📄 .gitignore
├── 📄 build-MinGW-W64.bat   # Windows build script
├── 📄 build-VisualStudio2022.bat  # VS build script
├── 📄 LICENSE
├── 📄 README.md</pre>