
const fs = require('fs');
const filePath = '/dev/stdin';
const input = fs.readFileSync(filePath, 'utf8').trim().split('\n');

const parse = str => str.split(' ');
const inf = Infinity;

const noteToNumber = { 
	'A': 0,
	'A#': 1,
	'B': 2,
	'C': 3,
	'C#': 4,
	'D': 5,
	'D#': 6,
	'E': 7,
	'F': 8,
	'F#': 9,
	'G': 10,
	'G#': 11,
};

const bruteforce = (index, notes, chord, press) => { 
	if (index === notes.length) { 
		let min = inf;
		let max = 0;

		const res = [];

		for (let i = 0; i < press.length; i++) { 
			res.push(noteToNumber[notes[i]] + press[i]);
			if (press[i] === 0) continue;
			min = Math.min(min, press[i]);
			max = Math.max(max, press[i]);
		}

		let cnt = 0;

		for (let i = 0; i < chord.length; i++) { 
			for (let j = 0; j < res.length; j++) { 
				if (res[j] % 12 === noteToNumber[chord[i]]) {
					cnt++;
					break;
				}
			}
		}

		if (cnt !== chord.length) return inf;
		if (max === 0) return 0;
		return max - min + 1;
	}

	let ret =  inf;

	for (let i = 0; i < chord.length; i++) { 
		let comp = noteToNumber[chord[i]];
		let open = noteToNumber[notes[index]];

		let toPress = (comp - open + 12) % 12;

		let lowest =  bruteforce(index + 1, notes, chord, [...press, toPress]);
		let highest = bruteforce(index + 1, notes, chord, [...press, toPress + 12]);

		ret = Math.min(ret, lowest, highest);
	}

	return ret;
}

const solve = () => { 
	const [N, M] = parse(input[0]).map(Number);

	const notes = parse(input[1]);
	const chord = parse(input[2]);

	const result = bruteforce(0, notes, chord, []);

	console.log(result);
}

solve();