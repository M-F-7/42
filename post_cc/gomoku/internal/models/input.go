package models


import (
    "github.com/hajimehoshi/ebiten"
	// "gomoku/internal/constant"
	"os"
	"fmt"
)

type Input struct{
	keyPressed bool
	MousePressed bool
	MousePosX int
	MousePosY int
	hide bool
}


func (i *Input) HandleInput(){
	if ebiten.IsKeyPressed(ebiten.KeyEscape){
		i.keyPressed = true
		fmt.Println("Game closed by pressing ESC")
		os.Exit(0)
	}
	if ebiten.IsMouseButtonPressed(ebiten.MouseButtonLeft){
		i.MousePressed = true
		i.MousePosX, i.MousePosY = ebiten.CursorPosition()
	}
}




func (i *Input) SetCursorVisible(visible bool){
    i.hide = visible
}

func (i *Input) GetMousePressed()(bool){
	return i.MousePressed
}

func (i *Input) SetMousePressed(state bool){
	i.MousePressed = state
}