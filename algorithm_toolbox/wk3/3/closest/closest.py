#Uses python3
import sys
import math

def small_search(pts, l, r, mid, min_dis):
	min_dis = math.sqrt(min_dis)
	pts = pts[l:r+1]
	pts = sorted(pts, key = lambda x:x[1])
	for i in range(0, len(pts)-1):
		for j in range(i +1, len(pts)):
			if(pts[j][1] - pts[i][1] >min_dis):
				break
			else:
				dist = math.sqrt(pow(pts[i][0]-pts[j][0],2)+ pow(pts[i][1]-pts[j][1],2))
				if dist < min_dis:
					min_dis = dist
	return min_dis**2

def helper(pts, l, r):
	if l >= r:
		return float('inf')
	if r - l == 1:
		return pow(pts[l][0]-pts[r][0],2)+ pow(pts[l][1]-pts[r][1],2)
	mid = l + (r - l)//2
	dist1 = helper(pts, l, mid)
	dist2 = helper(pts, mid+1, r)
	dmin = min(dist1, dist2)
	l_tmp = mid
	r_tmp = mid
	while pts[mid][0]-pts[l_tmp][0] < math.sqrt(dmin) and l_tmp > l:
		l_tmp -= 1
	while pts[r_tmp][0] - pts[mid][0] < math.sqrt(dmin) and r_tmp < r:
		r_tmp += 1

	d = small_search(pts, l_tmp, r_tmp, mid, dmin)
	ans = min(dmin,d)
	return ans

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n = data[0]
    x = data[1::2]
    y = data[2::2]
    pts = []
    for i in range(len(x)):
    	pts.append((x[i], y[i]))
    pts = sorted(pts, key = lambda x:x[0])
    ans = helper(pts, 0, len(pts)-1)
    print("{0:.9f}".format(math.sqrt(ans)))
