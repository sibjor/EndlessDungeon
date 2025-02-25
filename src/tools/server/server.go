package main

import (
	"fmt"
	"net/http"
	"os"
	"path/filepath"
	"strings"
)

// findFilePath searches for the requested file by traversing up the directory structure
func findFilePath(fileName string) (string, error) {
	// Start from the current working directory
	dir, err := os.Getwd()
	if err != nil {
		return "", err
	}

	for {
		// Check if the requested file exists in the build-web directory
		path := filepath.Join(dir, "build-web", fileName)
		fmt.Println("Checking path:", path) // Debug print
		if _, err := os.Stat(path); err == nil {
			fmt.Println("Found file at:", path) // Debug print
			return path, nil
		} else {
			fmt.Println("File not found at:", path) // Debug print
		}

		// Move up one directory
		parentDir := filepath.Dir(dir)
		if parentDir == dir {
			break // Reached the root directory
		}
		dir = parentDir
	}

	return "", fmt.Errorf("%s not found", fileName)
}

// handler handles HTTP requests
func handler(w http.ResponseWriter, r *http.Request) {
	// Extract the requested file name from the URL path
	fileName := strings.TrimPrefix(r.URL.Path, "/")
	if fileName == "" {
		fileName = "EndlessDungeon.html"
	}

	// Find the file path
	filePath, err := findFilePath(fileName)
	if err != nil {
		http.Error(w, "File not found", http.StatusNotFound)
		return
	}

	// Set the correct MIME type for JavaScript and WebAssembly files
	if strings.HasSuffix(fileName, ".js") {
		w.Header().Set("Content-Type", "application/javascript")
	} else if strings.HasSuffix(fileName, ".wasm") {
		w.Header().Set("Content-Type", "application/wasm")
	}

	// Serve the file
	http.ServeFile(w, r, filePath)
}

func main() {
	// Set up handler to handle all requests
	http.HandleFunc("/", handler)
	fmt.Println("Server running on port 8888")

	// Start the HTTP server on port 8888
	if err := http.ListenAndServe(":8888", nil); err != nil {
		fmt.Println("Error starting server:", err)
	}
}
