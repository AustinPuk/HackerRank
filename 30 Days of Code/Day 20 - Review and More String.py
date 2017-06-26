
try:
  s = raw_input().strip()
except:
  print 0
  pass

print s

delimiters = [' ', '!', '[', ',', '?', '.', '\\', '\'',  '_', '@', '+', ']']


tempString = ""
words = []

for letter in s:
  if letter in delimiters:
    if len(tempString) > 0:
      words.append(tempString)
      tempString = ""
  else:
    tempString += letter

if len(tempString) > 0:
  words.append(tempString)

print len(words)
for i in xrange(len(words)):
  print words[i]