package utils

import (

)

func Find(tab []int, pos int, slice int) (bool){
	for i := range tab{
		if pos <= tab[i] + slice && pos >= tab[i] - slice {	
			return true
		}
	}	
	return false
}	