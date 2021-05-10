import sys


def k_means(k, max_iter):
    
     list_of_data = load_input()
      
     list_of_centers = list_of_data[:k]  #centoids
     points = [[] for i in range(k)]  #points of centroids by index
     
   
     for i in range(max_iter): #condition 1
        
             temp_List_of_centers = [j for j in list_of_centers]  #make another list of centroids in order to check consition 2
             
             for p in list_of_data:      #update distance and index odistances_from_centersf centroids
                 distances_from_centers = [distance(p, c) for c in list_of_centers]

                 minimum_center = min(distances_from_centers, key = lambda x:float(x))
                 minimum_center = distances_from_centers.index(minimum_center) 
                 
                 points[minimum_center].append(p)
                       
             for j in range(k):  #update means
                  list_of_centers[j] = mean(points[j], len(list_of_centers[0]) )
             
             if temp_List_of_centers == list_of_centers: #condition 2
                 break
     
             points = [[] for i in range(k)]
         
     return list_of_centers


def load_input():
    list_of_data = []
      
    while True:
         try: 
             l = input()
             list_of_data.append([float(x) for x in l.split(",")])
         except EOFError:
             break
         
    return list_of_data


 
    
def distance(p, c):
    sum_of_distances = 0
    i = 0
    while True:
        try:
           sum_of_distances += (p[i]-c[i])**2
           i = i+1
        except Exception:
           break
    
    return sum_of_distances



def mean(points, y):
    
    sum_of_point = [0 for i in range(y)]
    
    for point in points:
        sum_of_point = [(sum_of_point[i] + point[i]) for i in range(y)]
    
    return [(j / len(points)) for j in sum_of_point]
  
    



if  len(sys.argv) > 3 or len(sys.argv) < 2 :
        sys.exit(1)
        
k = int(sys.argv[1])    
max_iter = 200

if len(sys.argv) == 3:
    max_iter = int(sys.argv[2])

assert k > 0
assert max_iter > 0
            
res = k_means(k, max_iter)

for point in res:
        print(','.join(["{:.4f}".format(x) for x in point]))