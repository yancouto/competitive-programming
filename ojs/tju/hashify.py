import hashlib,sys
 
m = hashlib.md5()
for line in sys.stdin.readlines():
    safe = line
    if line.find("//") != -1:
        line = line[:line.find("//")]
    trimmed = line.replace(" ","").replace("\n","").replace("\t","")
    m.update(trimmed)
    hash = m.hexdigest()[:4]
    print "%s %s"%(hash,safe),
