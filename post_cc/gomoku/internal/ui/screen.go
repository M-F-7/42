package ui

import (
	// "image/color"
    // "log"
    // "fmt"
    // "errors"
    // "image/color"
    "github.com/hajimehoshi/ebiten"
    // "github.com/hajimehoshi/ebiten/ebitenutil"
    "gomoku/internal/constant"
)

type Screen struct{
    // Assets *Assets
    width int
    height int
    name string
}


func StartScreen(){

    screen := &Screen{
        width: constant.WidthScreen,
        height: constant.HeightScreen,
        name: "GOATMOKU",
    }
    ebiten.SetWindowSize(screen.width, screen.height)
    ebiten.SetWindowTitle(screen.name)
}


// func (s *Screen) Draw(image *ebiten.Image){
//     var start_x float64 = constant.WidthScreen / 4
//     var start_y float64 = 100
//     for i := 0; i < 19; i++{
//         for j := 0; j < 19; j++{
//             ebitenutil.DrawRect(image, start_x, start_y, s.Assets.Stone.Width, s.Assets.Stone.Height, color.White)
//             start_x += s.Assets.Stone.Width * 1.1
//         }
//         start_y += s.Assets.Stone.Height * 1.1
//         start_x = constant.WidthScreen / 4
//     }
//     // image.Fill(color.RGBA{255, 0, 0, 255})
    
//     // op := &ebiten.DrawImageOptions{}
//     // op.GeoM.Translate(500, 500)

//     // // image.DrawImage(image, op)
//     // image.DrawImage(s.Assets.Stone, op)
// }

func (s *Screen) Layout(w, h int) (int, int){
    return constant.WidthScreen, constant.HeightScreen 
}