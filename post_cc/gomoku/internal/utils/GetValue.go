package utils

import (

)

func GetValue(tab []int, pos int, slice int) (float64){
	for i := range tab{
		if pos <= tab[i] + slice && pos >= tab[i] - slice {	
			return float64(tab[i])
		}
	}	
	return -1
}	