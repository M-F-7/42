package models

import (
	"gomoku/internal/constant"
)
type Board struct {
	Cells [][]int
	Start_x int
	Start_y int
	StepsX []int
	StepsY []int
}

func NewBoard() *Board {
	tab := make([][]int, constant.BoardSize)
	for i := range tab {
		 tab[i] = make([]int, constant.BoardSize)
	}

	var j int = 0
	sX := make([] int, constant.BoardSize)
	curr_x := constant.BoardStartX
	for j < constant.BoardSize{
		curr_x += constant.WidthCell
		sX[j] = curr_x
		j += 1
	}

	var k int = 0
	sY := make([] int, constant.BoardSize)
	curr_y := constant.BoardStartY
	for k < constant.BoardSize{
		curr_y += constant.WidthCell
		sY[k] = curr_y
		k +=1
	}
	return &Board{
		Cells:tab,
		Start_x: constant.BoardStartX,
		Start_y: constant.BoardStartY,
		StepsX: sX,
		StepsY: sY,
	}
}


// func 