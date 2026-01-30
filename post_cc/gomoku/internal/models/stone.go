package models

import (
    "github.com/hajimehoshi/ebiten"
	// "gomoku/internal/utils"
	"gomoku/internal/constant"
	"github.com/hajimehoshi/ebiten/ebitenutil"
	"image/color"
)

type Stone struct {
	img *ebiten.Image
	width float64
	height float64
	color color.RGBA
}


func NewStone(img *ebiten.Image) *Stone {
	img, err := ebiten.NewImage(constant.HeightScreen / 2, constant.WidthScreen / 2, ebiten.FilterLinear)
	_ = err
	colour := color.RGBA{R: 255, G: 0, B: 0, A: 255}
	img.Fill(colour)
    return &Stone{
        width:  constant.WidthStone,
        height: constant.HeightStone,
        img:    img,
		color: colour,
    }
}

func (s *Stone) Draw(image *ebiten.Image, x float64, y float64){
        ebitenutil.DrawRect(image, x, y, s.width, s.height, s.color)
}