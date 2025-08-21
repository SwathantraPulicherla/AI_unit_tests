# Path to your test file
$TestFile = "tests/test_calculator.c"

# Get unstaged changes only for .c files
$Changes = git diff -- '*.c'

if ([string]::IsNullOrWhiteSpace($Changes)) {
    Write-Host "No changes in C source files."
    exit 0
}

# Save changes to a temp file (optional, for debugging)
$Changes | Out-File changes.diff -Encoding utf8

# Extract newly added or modified function names
# Lines starting with "+" and containing "(" but not "+++"
$FuncNames = $Changes -split "`n" | Where-Object { $_ -match '^\+.*\(' -and $_ -notmatch '^\+\+\+' } |
    ForEach-Object {
        # Remove '+' at the start
        $line = $_ -replace '^\+','' -replace ';.*',''

        # Extract only the function name (after return type)
        if ($line -match '^\s*\w+\s+(\w+)\s*\(') {
            $matches[1]
        }
    } | ForEach-Object { $_.Trim() } | Sort-Object -Unique

if ($FuncNames.Count -eq 0) {
    Write-Host "No new functions found in .c files."
    exit 0
}

# Append placeholders to test file
Add-Content $TestFile "`n// Copilot placeholders for new functions:"
foreach ($func in $FuncNames) {
    $stub = @"
void test_$func() {
    // Copilot can suggest test here
}
"@
    Add-Content $TestFile $stub
}

Write-Host "Placeholders appended to $TestFile. Open the file and let Copilot suggest test cases."