package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

func init() {
	rand.Seed(time.Now().UnixNano())
}

type Kei []string

func KeiChan() *Kei {
	return &Kei{"先生を", "殺して", "私も", "死にます"}
}

func (k *Kei) Shuffle() *Kei {
	n := len(*k)
	for i := n - 1; i >= 0; i-- {
		j := rand.Intn(i + 1)
		(*k)[i], (*k)[j] = (*k)[j], (*k)[i]
	}
	return k
}

func (k *Kei) WorkUntil(f func()) {
	for len(*k) > 0 {
		f()
	}
}

func (k *Kei) Take(n int) *Kei {
	rn := n
	if len(*k) < rn {
		rn = len(*k)
	}
	r := (*k)[:rn]
	*k = (*k)[rn:]
	for len(r) < n {
		r = append(r, "")
	}
	return &r
}

func (k *Kei) Kawaii() (r string) {
	k.Shuffle().WorkUntil(func() {
		sk := Kei{}
		for _, s := range *k.Take(2) {
			sk = append(sk, s)
		}

		ss := Kei{}
		for _, s := range sk {
			rs := []rune(s)
			rw := int(math.Ceil(float64(len(rs)) / 2))
			ss = append(ss, string(rs[:rw]))
			ss = append(ss, string(rs[rw:]))
		}
		rs := *(&ss).Take(4)
		if rand.Int()%2 == 0 {
			rs[0], rs[1], rs[2], rs[3] = rs[2], rs[1], rs[0], rs[3]
		}
		if r == "" {
			r += rs[0] + rs[1] + rs[2] + rs[3] + "、"
		} else {
			r += rs[0] + rs[1] + rs[2] + rs[3]
		}
	})
	return r
}

func main() {
	i := 1
	for {
		s := KeiChan().Kawaii()
		fmt.Printf("[%d] %s\n", i, s)
		if s == "先生を殺して、私も死にます" {
			break
		}
		i++
	}
}
