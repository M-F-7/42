package models

import (
	"github.com/hajimehoshi/ebiten"
	"github.com/hajimehoshi/ebiten/ebitenutil"
	"gomoku/internal/constant"
	"image/color"
)

type Cell struct {
	Width float64
	Height float64
	color color.RGBA
	img *ebiten.Image
}



func NewCell(img *ebiten.Image) *Cell {
	image, err := ebiten.NewImage(constant.HeightScreen / 2, constant.WidthScreen / 2, ebiten.FilterLinear)
	_ = err
	colour := color.RGBA{R: 214, G: 178, B: 120, A: 255}
	image.Fill(colour)
    return &Cell{
        Width:  constant.WidthCell,
        Height: constant.HeightCell,
		color: colour,
        img:    img,
    }
}

func (c *Cell) Draw(image *ebiten.Image){
	var s_x float64 = constant.BoardStartX
    var s_y float64 = constant.BoardStartY
    for i := 0; i < constant.BoardSize; i++{
        for j := 0; j < constant.BoardSize; j++{
            ebitenutil.DrawRect(image, s_x, s_y, c.Width, c.Height, c.color)
            s_x += c.Width * 1.05
        }
        s_y += c.Height * 1.05
        s_x = constant.WidthScreen / 4
    }
    
    // op := &ebiten.DrawImageOptions{}
    // op.GeoM.Translate(500, 500)

    // // image.DrawImage(image, op)
    // image.DrawImage(s.Assets.Cell, op)
}