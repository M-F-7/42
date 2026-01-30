package main

import (
	// "fmt"
	"gomoku/internal/game"
	// "gomoku/internal/models"
	"gomoku/internal/ui"
	// "github.com/hajimehoshi/ebiten"
)

func main() {
	ui.StartScreen()
	game.StartGameLoop()
}