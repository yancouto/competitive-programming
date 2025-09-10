# regenerates random seeds for all generated tests
import os, random, re

# use this to have a fixed seed, for example, 12345
# or comment it out to have a different seed every time
#random.seed(12345)

with open('gen_all.sh', 'rt') as fin:
	with open('gen_all.sh.new', 'wb') as fout:
		for line in fin:
			line = line.strip()
			if line != "#!/bin/bash":
				seed = random.randrange(10 ** 8, 10 ** 9)
				line = re.sub("seed[0-9]+", "seed" + str(seed), line)
			fout.write((line + '\n').encode())

os.remove('gen_all.sh')
os.rename('gen_all.sh.new', 'gen_all.sh')
