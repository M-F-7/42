package utils

import (

)

func GetIdx(tab []int, pos int, slice int) (int){
	for i := range tab{
		if pos <= tab[i] + slice && pos >= tab[i] - slice {	
			return i
		}
	}
	return -1	
}