
N = int(raw_input().strip())
array = map(int, raw_input().split())

#Insertion Sort (Or can just use array.sort())
for i in range(1, len(array)):
  currentValue = array[i]
  for j in range(0, i):
    if currentValue < array[j]:
      array.insert(j, array.pop(i))
      break

result = []
currentMin = float("inf")
for i in range(0, len(array) - 1):
  diff = abs(array[i] - array[i + 1])
  if  diff < currentMin:
    currentMin = diff
    result = [array[i], array[i + 1]]
  elif diff == currentMin:
    result.append(array[i])
    result.append(array[i + 1])

for i in range(len(result)):
  print result[i],