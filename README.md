# Project PRPR 2025 — Sudoku Records Management

A C console application that manages Sudoku game records, player records, and
competition results stored in text files. The program reads single-letter
commands from standard input and manipulates the data using three different
storage strategies over the course of the project: **dynamically allocated
arrays**, then a **singly linked list of structures**.

## Input Files

The program works with three text files, each containing one record per line,
fields separated by `#`.

### `Sudoku.txt`
```
SID<difficulty><nnnn>#<81 digits>#
```
- `SID` — literal prefix
- `<difficulty>` — one uppercase letter `A`–`Z`
- `<nnnn>` — 4-digit game number (`0000`–`9999`)
- `#` separator
- 81 digits (`1`–`9`), the flattened 9×9 solution grid
- `#` separator

Example:
```
SIDA0001#421675389967318245853492617198742563734856129526139748216837954573491682984265371#
```

### `PlayersRegister.txt`
```
PID<quality><nnnnn>#<Name>#<Country>#<YearOfBirth>#
```
- `PID` — literal prefix
- `<quality>` — one letter `a`–`z` or `A`–`Z` (player quality/rank)
- `<nnnnn>` — 5-digit player number (`00000`–`99999`)
- `#` separator
- First and last name (may be empty)
- `#` separator
- Country (may be empty)
- `#` separator
- Year of birth (may be empty)
- `#` separator

Exactly 4 `#` separators per line; the `PID` identifier itself is mandatory,
all other fields may be empty. Max line length: 500 characters.

Example:
```
PIDa00001#Novak Peter#Slovakia#1998#
```

### `SolutionsRegister.txt`
```
GID<difficulty><nnn>#<PID>#<SID>#<YYYYMMDD>#<minutes>#<seconds>#
```
- `GID` — literal prefix (competition identifier)
- `<difficulty>` — one lowercase letter `a`–`z` (competition difficulty)
- `<nnn>` — 3-digit competition number (`000`–`999`)
- `#` separator
- Player identifier (`PID...`)
- `#` separator
- Game identifier (`SID...`)
- `#` separator
- Date solved, `YYYYMMDD`
- `#` separator
- Solution duration: minutes
- `#` separator
- Solution duration: seconds
- `#` separator

Example:
```
GIDa125#PIDa00001#SIDA0001#20251010#12#45#
```

## Commands

Commands are single lowercase letters read from stdin, one per line
(some are followed by additional arguments/parameters).

| Cmd | Description |
|---|---|
| `v <n>` | Print a listing, where `<n>` selects the source: `1` = raw file records, `2` = dynamic arrays, `3` = merged linked list. Invalid `<n>` → `V: Incorrect listing selection.` |
| `h` | Read a game (`SID`) identifier from input; write all results for that game (file order, sorted by `GID`) to `Output_H.txt`. |
| `n` | Count records in each txt file and build dynamically allocated arrays for each field (no structs). Rebuilds/frees previous arrays if they exist. |
| `m` | Load `PlayersRegister.txt` and `SolutionsRegister.txt` into a linked list of structures, merging each player with their results. Frees any previous list first. |
| `q <Y>` | Read a new solution record from stdin and insert it into the dynamic arrays at position `Y` (1-indexed; beyond array length → appended). Validates input format, re-prompting on error. |
| `w` | Read a `PID`; delete all matching records from the dynamic solutions arrays, compacting memory. |
| `e <SID> <X>` | Write the full Sudoku grid for `<SID>` to `Output_E.txt`, with `X` (1–5) randomly blanked cells per row. |
| `a <Y>` | Read a new player from stdin (name, country, year) and insert into the merged linked list at position `Y`. Rejects duplicates (same name + birth year); auto-assigns a new `PID` with quality letter `a`. |
| `s` | Read a `GID`; delete all matching results from the merged linked list. |
| `d` | Sort each player's results within the linked list by solve duration (ascending). No output. |
| `k` | Free all dynamically allocated memory (arrays and linked list), close open files, and terminate the program. No output. |

### Command details & status messages

- **`v` (listing):**
  - `v 1` — opens all three files if not already open. If any fails to open:
    `V1: Unopened txt files.` Otherwise prints each player's identifier,
    name, country, year, and up to 10 sample results (as found directly in
    the raw files), separated by blank lines.
  - `v 2` — requires arrays built via `n`; if not: `V2: Unfilled arrays.`
    Otherwise prints `PID / YearOfBirth / Country`, `Identity`, and up to
    10 tab-indented `Result` lines per player from the dynamic arrays.
  - `v 3` — requires the merged list via `m`; if not: `V3: Merge list not
    filled.` Otherwise prints `PID`, `Identity`, `Country`, `YearOfBirth`,
    and each result line as `SID / DifficultyOfGame / GID /
    DifficultyOfCompetition / GameDate / Duration(seconds)`.
  - Any other value → `V: Incorrect listing selection.`
- **`h`:** Works once files are open (`v1` or `n`). Success →
  `H: Summary successfully created.`; files not open →
  `H: Unopened txt file.`; bad game id → `H: Incorrect input.`
- **`n`:** Requires files open (`v1`); otherwise `N: File not open.`
  No output on success.
- **`m`:** Requires files open (`v1`); otherwise `M: Unopened file.`
  On success: `M: <n> records read.`
- **`q`:** Requires arrays from `n`; otherwise `Q: Arrays are not created`.
  Invalid field format re-prompts: `Q: incorrect input format, enter
  again:`.
- **`w`:** On success: `W: Deleted: <n> record(s)!`; if arrays missing:
  `W: Arrays are not created.`
- **`e`:** Requires arrays from `n`; missing → `E: Arrays are not created.`;
  bad input → `E: Incorrect input.`
- **`a`:** On success: `A: Record successfully added to position <Y>.`;
  on duplicate: `A: Duplicate record.` Works even if `m` hasn't run yet
  (creates/prepends to the list).
- **`s`:** On success: `S: Deleted: <n> records!`; if list missing:
  `S: Linked list has not been created.`
- **`d`, `k`:** No output.

## Implementation Requirements

- **Language:** C.
- Each command is implemented in its **own function**; state is passed via
  **arguments**, not global variables.
- Commands `n`, `q`, `w`, `e` must use **dynamically allocated arrays**
  (`malloc`/friends) — **no structs** for these.
- Commands `m`, `a`, `s`, `d` must use a **singly/doubly linked list of
  structures**.
- Do not load an entire input file into a single dynamic array — allocate
  per-field arrays.
- All dynamic memory must be correctly freed (on rebuild via `n`/`m`, and
  finally on `k`).
- Input values (from files and console) may be assumed valid/well-formed
  except where explicit validation is called out (e.g. `q`).
- Output formatting must match the specification **exactly** — deviations
  are penalized.
- Source code should be clearly written and commented.

## Output Files

- `Output_H.txt` — written by `h`, results for a given game.
- `Output_E.txt` — written by `e`, a Sudoku grid with random cells blanked.

## Build & Run

```bash
gcc -std=c11 -Wall -Wextra -o prpr StudentID_project_vX.c
./prpr
```

Commands are then typed on stdin, e.g.:
```
v 1
n
v 2
h
SIDB0002
k
```

## Submission

- Submit only the `*.c` source file to the designated AIS location (no
  `*.zip`, `*.exe`, or other file types).
- File naming: `StudentID_project_v1.c`, `StudentID_project_v2.c`,
  `StudentID_project_v3.c` for each submission phase.
- Work must be done independently; submissions are compared for
  similarity, with matches referred to the disciplinary committee.
- A personal presentation of the project to the trainer is required after
  the second or third submission (worth up to 3.0 points).

### Grading phases & deadlines

| Version | Deadline | Evaluated commands | Max points (this phase) |
|---|---|---|---|
| v1 | 27.10.2024 23:59:59 | `v1`, `v`, `h` | 1.4 (`v1`) + 0.3 (`v` other) + 1.9 (`h`) |
| v2 | 10.11.2024 23:59:59 | `n`, `q`, `w`, `e`, `v2` | 2.2 + 2.3 + 2.3 + 1.9 + 1.8 |
| v3 | 1.12.2024 23:59:59 | `m`, `a`, `s`, `d`, `v3`, `k` | 4.0 + 2.8 + 3.4 + 2.4 + 2.0 + 3.4 |

Plus: 3.0 points for the personal presentation.

> **Note:** If a command from phase 1 or 2 is instead first submitted in a
> later phase, only **60%** of the points otherwise available for that
> command are awarded.
