# PLYR

**PLYR** is a lightweight, Raylib-based music player designed for simplicity and ease of use. The app reads audio files from your `XDG_MUSIC_DIR` environment variable (usually `~/Music` on most Unix-like systems), extracts metadata (artist, title, album, track number) using TagLib, and provides an intuitive, scrollable UI to manage and play your music.

## Features

- **Automatic Directory Reading**: Reads audio files from the directory specified by the `XDG_MUSIC_DIR` environment variable (defaults to `~/Music`).
- **Metadata Extraction**: Automatically extracts and displays metadata (Artist, Title, Album, and Track Number) for MP3 files using TagLib.
- **Lazy Metadata Loading**: Metadata is loaded in the background to keep the UI responsive.
- **Scrollable List**: Easily navigate through your playlist with a scrollable list UI.
- **Track Sorting**: Songs are grouped by album and sorted by track number within each album.
- **Basic Playback Controls**: Play, pause, and resume music playback, with a progress bar to visualize the current position in the track.
- **MP3 Support**: Currently supports MP3 files only.

## Screenshots

<img width="800" alt="image" src="https://github.com/user-attachments/assets/197058e4-344a-4bea-bc36-03f58a953275">


## Getting Started

### Prerequisites

Make sure you have the following dependencies installed:

- **Meson**: Build system to configure and manage your build.
- **Ninja**: Build tool that Meson uses by default.
- **Raylib**: The core library for handling graphics and audio.
- **TagLib**: Library for reading and writing metadata in audio files.

Install dependencies with your package manager. For example:

```bash
# On Ubuntu or Debian-based systems
sudo apt install meson ninja-build libtagc0-dev libraylib-dev

# On macOS with Homebrew
brew install meson ninja taglib raylib
```

### Clone the Repository

```bash
git clone https://github.com/znschaffer/plyr.git
cd plyr
```

## Compile

1. **Configure the Build Directory**:

   First, create a build directory and configure it with Meson.

   ```bash
   meson setup builddir
   ```

2. **Build the Project**:

   Navigate to the `builddir` and compile the project using Ninja.

   ```bash
   meson compile -C builddir
   ```

3. **Run the Application**:

   After compiling, run the application from the `builddir`:

   ```bash
   cp -r resources/fonts ./builddir
   ./builddir/plyr
   ```

### Cleaning the Build

To clean the build artifacts:

```bash
meson compile -C builddir --clean
```

### Rebuilding

If you make changes and need to rebuild, simply run:

```bash
meson compile -C builddir
```

## Usage

- **Automatic Directory Reading**: The app reads MP3 files from the directory specified by the `XDG_MUSIC_DIR` environment variable (defaults to `~/Music`). Ensure that this environment variable is set correctly to point to your music directory.
- **Playback Controls**: Use the spacebar to restart the current song, and press `p` to toggle between play and pause.
- **Track Sorting**: Songs are automatically grouped by album and sorted by track number within each album.

## Contributing

Contributions are welcome! Feel free to submit a pull request or open an issue if you have any suggestions or bug reports.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
