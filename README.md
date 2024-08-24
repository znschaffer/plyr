Here's a README template for your project:

---

# PLYR

PLYR is a lightweight, customizable audio player built with [Raylib](https://www.raylib.com/) for the UI and [TagLib](https://taglib.org/) for audio metadata extraction. The application features a scrollable list of audio files, lazy loading of metadata, search functionality, and drag-and-drop file queuing. It is designed to be responsive and intuitive, with support for album-based sorting and track number organization.

## Features

- **Audio Playback**: Supports popular audio formats such as MP3.
- **Metadata Extraction**: Uses TagLib to extract artist, title, album, and track number for each audio file.
- **Scrollable Audio List**: Easily browse through your audio files in a scrollable list.
- **Lazy Metadata Loading**: Audio metadata is loaded in the background for optimal performance.
- **Search Functionality**: Filter your audio files by artist, title, or album using a search input box.
- **Drag-and-Drop Support**: Add new audio files to the queue by dragging and dropping them into the app.
- **Album Sorting**: Audio files are grouped by album and sorted by track number within each album.

## Installation

1. **Clone the Repository**:
   ```sh
   git clone https://github.com/yourusername/plyr.git
   cd plyr
   ```

2. **Install Dependencies**:
   Ensure that Raylib and TagLib are installed on your system. You can use the following command for installation on a Debian-based system:
   ```sh
   sudo apt-get install libraylib-dev libtag1-dev
   ```

3. **Compile the Project**:
   Compile the project using `make`:
   ```sh
   make
   ```

4. **Run the Application**:
   ```sh
   ./plyr
   ```

## Usage

- **Navigating the List**: Scroll through your audio files using the mouse wheel or arrow keys.
- **Playing Audio**: Click on an audio file to load and play it.
- **Searching**: Type in the search box to filter the list by artist, title, or album.
- **Drag-and-Drop**: Drag audio files into the app window to add them to the list.
- **Album Sorting**: Files are automatically grouped by album and sorted by track number within each album.

## Future Enhancements

- **Support for More Audio Formats**: Expand support to additional audio formats.
- **Improved UI Customization**: Enhance the UI with more customization options.
- **Playlist Management**: Add playlist creation and management features.
- **Equalizer and Audio Effects**: Include an equalizer and other audio effects.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your improvements.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Acknowledgments

- [Raylib](https://www.raylib.com/) - A simple and easy-to-use library to enjoy videogames programming.
- [TagLib](https://taglib.org/) - A library for reading and editing audio file metadata.

---

Feel free to adjust any details to better fit your project's specific needs.
