package game

import (
	"fmt"
	// "image/color"
	"gomoku/internal/models"
	"gomoku/internal/ui"
	"gomoku/internal/utils"
	"gomoku/internal/constant"
	"github.com/hajimehoshi/ebiten"
)

type GameLoop struct{
	board *models.Board
	input *models.Input
	screen *ui.Screen
	assets *ui.Assets
}




func  StartGameLoop(){
	gl := &GameLoop{
		board: models.NewBoard(),
		input:  &models.Input{},
    	screen: &ui.Screen{},
		assets: &ui.Assets{
			Cell: func() *models.Cell {
            	return models.NewCell(nil)
            }(),
			Stone: func() *models.Stone {
            	return models.NewStone(nil)
            }(),
		},
	}
	ebiten.RunGame(gl)
}


func (gl *GameLoop) Update(screen *ebiten.Image) error{
	if ebiten.IsRunningSlowly() {
		// fmt.Println("The game wasnt running correctly")
		gl.input.HandleInput()
		if (gl.input.GetMousePressed()){
			if (gl.checkPos()){
				x := utils.GetIdx(gl.board.StepsX, gl.input.MousePosX, constant.SliceX)
				y := utils.GetIdx(gl.board.StepsY, gl.input.MousePosY, constant.SliceY)
				gl.board.Cells[x][y] = 1
				// gl.assets.Stone.Draw(screen, float64(x), float64(y))
			}
			gl.input.SetMousePressed(false)
		}
		return nil
    }
	gl.input.HandleInput()
	gl.checkPos()
    return nil
}

func (gl *GameLoop) Draw(screen *ebiten.Image) {
    // gl.screen.Draw(screen)
	gl.assets.Cell.Draw(screen)
	for y := range gl.board.Cells{
		for x := range gl.board.Cells[y]{
			if gl.board.Cells[y][x] == 1{
				// vX := utils.GetValue(gl.board.StepsX, x, constant.SliceX)
				// vY := utils.GetValue(gl.board.StepsY, y, constant.SliceY)
				px := gl.board.StepsX[x]
				py := gl.board.StepsY[y]
            	gl.assets.Stone.Draw(screen, float64(px), float64(py))
				// fmt.Println(vX, vY)
				// gl.assets.Stone.Draw(screen, vX, vY)
			}
		}
	}
}

func (gl *GameLoop) Layout(w, h int) (int, int) {
    return gl.screen.Layout(w, h)
}


func (gl *GameLoop) checkPos()(bool){
	fmt.Println(gl.board.StepsX)
	fmt.Println(gl.input.MousePosX)
	fmt.Println(gl.board.StepsY)
	fmt.Println(gl.input.MousePosY)
	if gl.input.MousePosX < gl.board.Start_x {
	    fmt.Println("CANNOT CLICK ❌: MousePosX < Start_x")
	    return false
	}

	if gl.input.MousePosX > gl.board.Start_x + constant.BoardSize * constant.WidthCell {
	    fmt.Println("CANNOT CLICK ❌: MousePosX > board max X")
	    return false
	}

	if gl.input.MousePosY < gl.board.Start_y{
	    fmt.Println("CANNOT CLICK ❌: MousePosY < Start_y")
	    return false
	}

	if gl.input.MousePosY > gl.board.Start_y + constant.BoardSize * constant.HeightCell {
	    fmt.Println("CANNOT CLICK ❌: MousePosY > board max Y")
	    return false
	}

	if gl.input.MousePosX <= gl.board.Start_x + constant.WidthCell - constant.SliceX {
	    fmt.Println("CANNOT CLICK 2❌: MousePosX too close to start")
	    return false
	}

	if gl.input.MousePosY <= gl.board.Start_y + constant.HeightCell - constant.SliceY {
	    fmt.Println("CANNOT CLICK 2❌: MousePosY too close to start")
	    return false
	}
	if !utils.Find(gl.board.StepsX, gl.input.MousePosX, constant.SliceX) || !utils.Find(gl.board.StepsY, gl.input.MousePosY, constant.SliceY) {
	    fmt.Println("CANNOT CLICK 3❌: Not on a corner")
	    return false
	}else {
		fmt.Println("🟩 Clic gauche à : ", gl.input.MousePosX, gl.input.MousePosY)
		return true
	}
}