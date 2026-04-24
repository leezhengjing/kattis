# Kattis Submissions (CS3233 @ NUS)

This repository contains my Kattis submissions and practice files for **CS3233 (Competitive Programming)** at NUS.

The folder layout intentionally follows my course progression and workflow based on Steven Halim's problem-solving approach, so directories are kept as-is.

## Repository Structure

- `week0` to `week13`: Weekly practice and submissions.
- `midterm2425`, `midterm2526`: Midterm preparation/submissions by academic year.
- `finals2425`, `finals2526`: Finals preparation/submissions by academic year.
- `methodstosolve`: Pattern-based practice and reference implementations grouped by topic/chapter.

Most problems include:

- Source code (`.cpp`, `.py`, etc.)
- Local sample/input notes (`.txt`)
- In some folders, local compile/run artifacts from practice

## Notes

- Solutions are primarily written for learning and contest practice, then submitted to Kattis.
- Code style may vary slightly over time as techniques evolve through the semester.
- This is a personal archive, not an official solution set.

## Typical Local Workflow

From a problem folder, for C++:

```bash
g++ -std=c++17 -O2 -pipe -o <prog> <file>.cpp
./<prog> < input.txt
```

For Python:

```bash
python3 <file>.py < input.txt
```

## License

Unless otherwise stated, this repository is for academic practice and personal reference.
