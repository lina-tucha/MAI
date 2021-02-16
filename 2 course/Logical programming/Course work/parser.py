file = open( "tree.ged", "r", encoding="utf-8")
inform = file.readlines()
file.close()

people = {}
ID = ""
name = ""
male = []
female = []

for line in inform:
    if(line.find('INDI', 0, len(line)-1)!=-1):
        word = line.split(' ')
        ID = word[1]
    elif ((line.find('GIVN',0,len(line)-1)!=-1)):
        word = line.split(' ')
        name = word[2].rstrip()
    elif ((line.find('SURN', 0, len(line) - 1) != -1)):
        word = line.split(' ')
        name = name + ' ' + word[2].rstrip()
        people[ID]= name
    elif ((line.find('SEX', 0, len(line) - 1) != -1)):
        word = line.split(' ')
        if (word[2].rstrip() == "F"):
            female.append([people[ID]])
        else: male.append([people[ID]])

mather = []
father = []
dad = ""
mom = ""

for line in inform:
    if(line.find('HUSB', 0, len(line)-1)!=-1):
        word = line.split(' ')
        dad = people[word[2].rstrip()]
    elif(line.find('WIFE', 0, len(line)-1)!=-1):
        word = line.split(' ')
        mom = people[word[2].rstrip()]
    elif(line.find('CHIL', 0, len(line)-1)!=-1):
        word = line.split(' ')
        mather.append([people[word[2].rstrip()], mom])
        father.append([people[word[2].rstrip()], dad])

outfile = open("mytree.pl", "w")

for i in mather:
    outfile.write("child('" + i[0] + "','" + i[1] + "').\n")
for i in father:
    outfile.write("child('" + i[0] + "','" + i[1] + "').\n")
for i in female:
    outfile.write("female('" + i[0] + "').\n")
for i in male:
    outfile.write("male('" + i[0] + "').\n")
outfile.close()
