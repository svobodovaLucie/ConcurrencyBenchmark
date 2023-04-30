import subprocess
import os
from typing import List

count_threadsanitizer = {'races': 0, 'no races': 0, 'errors': 0, 'timeout': 0}
count_helgrind = {'races': 0, 'no races': 0, 'errors': 0, 'timeout': 0}
count_coderrect = {'races': 0, 'no races': 0, 'errors': 0, 'timeout': 0}
count_darc = {'races': 0, 'no races': 0, 'errors': 0, 'timeout': 0}

timeout = 6 # seconds

def run_analysis_threadsanitizer_one_file(filename):
    global count_threadsanitizer
    try:
        p1 = subprocess.Popen(f"clang -fsanitize=thread -g {filename} && ./a.out 2>&1", shell=True, stdout=subprocess.PIPE)
        p2 = subprocess.Popen("grep -m 1 -E '(data race|clang: error)'", shell=True, stdin=p1.stdout, stdout=subprocess.PIPE)
        p1.stdout.close()
        output, error = p2.communicate(timeout=timeout)
        os.system(f"rm -rf ./*.o")
        if p2.returncode == 0:
            count_threadsanitizer['races'] += 1
            return "data race"
        elif p2.returncode == 1:
            count_threadsanitizer['no races'] += 1
            return "no data race"
        else: 
            count_threadsanitizer['errors'] += 1
            return "error (grep)"
    except subprocess.TimeoutExpired:
        p1.kill()
        p2.kill()
        count_threadsanitizer['timeout'] += 1
        return "timeout"

def run_analysis_helgrind_one_file(filename):
    global count_helgrind
    try:
        p1 = subprocess.Popen(f"gcc -pthread {filename} && valgrind --tool=helgrind ./a.out 2>&1", shell=True, stdout=subprocess.PIPE)
        p2 = subprocess.Popen("grep -m 1 -E 'data race|ERROR SUMMARY'", shell=True, stdin=p1.stdout, stdout=subprocess.PIPE)
        p1.stdout.close()
        output, error = p2.communicate(timeout=timeout)
        os.system(f"rm -rf ./*.o")
        if p2.returncode == 0:
            output_str = output.decode("utf-8")
            if 'data race' in output_str:
                count_helgrind['races'] += 1
                return "data race"
            elif 'ERROR SUMMARY' in output_str:
                count_helgrind['no races'] += 1
                return "no data race"
        elif p2.returncode == 1:
            count_helgrind['no races'] += 1
            return "no data race2"
        else: 
            count_helgrind['errors'] += 1
            return "error (grep)"
    except subprocess.TimeoutExpired:
        p1.kill()
        p2.kill()
        count_helgrind['timeout'] += 1
        return "timeout"

def run_analysis_coderrect_one_file(filename):
    global count_coderrect
    try:
        p1 = subprocess.Popen(f"coderrect -t gcc -pthread -g {filename} 2>/dev/null", shell=True, stdout=subprocess.PIPE)
        p2 = subprocess.Popen("grep -E 'data races'\|'No race'", shell=True, stdin=p1.stdout, stdout=subprocess.PIPE)
        p1.stdout.close()
        output, error = p2.communicate(timeout=timeout)
        os.system(f"rm -rf .coderrect/") 
        os.system(f"rm -rf ./*.o")
        if p2.returncode == 0:
            output_str = output.decode("utf-8")
            if 'data races' in output_str:
                count_coderrect['races'] += 1
                return "data race"
            elif 'No race' in output_str:
                count_coderrect['no races'] += 1
                return "no data race"
        elif p2.returncode == 1:
            count_coderrect['no races'] += 1
            return "no data race"
        else: 
            count_coderrect['errors'] += 1
            return "error (grep)"
    except subprocess.TimeoutExpired:
        p1.kill()
        p2.kill()
        count_coderrect['timeout'] += 1
        return "timeout"

def run_analysis_darc_one_file(filename):
    global count_darc
    try:
        p1 = subprocess.Popen(f"sudo infer --darc-only -- gcc -c {filename}", shell=True, stdout=subprocess.PIPE)
        p2 = subprocess.Popen("grep -m 1 -E '(Data race|No issues found)'", shell=True, stdin=p1.stdout, stdout=subprocess.PIPE)
        p1.stdout.close()
        output, error = p2.communicate(timeout=timeout)
        os.system(f"sudo rm -rf infer-out/") 
        os.system(f"rm -rf ./*.o")
        if p2.returncode == 0:
            output_str = output.decode("utf-8")
            if 'Data race' in output_str:
                count_darc['races'] += 1
                return "data race"
            elif 'No issues found' in output_str:
                count_darc['no races'] += 1
                return "no data race"
        elif p2.returncode == 1:
            count_darc['no races'] += 1
            return "no data race2"
        else: 
            count_darc['errors'] += 1
            return "error (grep)"
    except subprocess.TimeoutExpired:
        p1.kill()
        p2.kill()
        count_darc['timeout'] += 1
        return "timeout"



"""
#output = run_command(command, timeout)
output = run_analysis_threadsanitizer_one_file("token_ring_bad.c", timeout)
output2 = run_analysis_threadsanitizer_one_file("phase01_bad.c", timeout)
output3 = run_analysis_helgrind_one_file("token_ring_bad.c", timeout)
output4 = run_analysis_helgrind_one_file("phase01_bad.c", timeout)
output5 = run_analysis_coderrect_one_file("token_ring_bad.c", timeout)
output6 = run_analysis_coderrect_one_file("phase01_bad.c", timeout)
output7 = run_analysis_darc_one_file("token_ring_bad.c", timeout)
output8 = run_analysis_darc_one_file("phase01_bad.c", timeout)
with open("output.html", "w") as file:
    file.write(f"<html>{output}, {output2}, {output3}, {output4}, {output5}, {output6}, {output7}, {output8}<body>")
    file.write("</body></html>")
"""



def generate_table() -> str:
    table_html = '<table><tr><th>filename</th><th>DarC</th><th>O2/Coderrect</th><th>ThreadSanitizer</th><th>Helgrind</th></tr>'
    num_of_programs = 0
    
    for dirpath, _, filenames in os.walk('.'):
        # sort filenames alphabetically
        filenames = sorted(filenames)
        
        for filename in filenames:
            if filename.endswith('.c') or filename.endswith('.cpp'):
                c_file = os.path.join(dirpath, filename)
                num_of_programs += 1
                result_threadsanitizer = run_analysis_threadsanitizer_one_file(c_file)
                result_helgrind = run_analysis_helgrind_one_file(c_file)
                result_coderrect = run_analysis_coderrect_one_file(c_file)
                result_darc = run_analysis_darc_one_file(c_file)

                table_html += f'<tr><td>{filename}</td><td>{result_darc}</td><td>{result_coderrect}</td><td>{result_threadsanitizer}</td><td>{result_helgrind}</td></tr>'

    table_html += '</table>'
    table_html += '</br>'
    table_html += '<table><tr><th>analyser</th><th>data races</th><th>no data races</th><th>timeout</th><th>errors</th></tr>'
    table_html += f"<tr><td>DarC</td><td>{count_darc['races']}</td><td>{count_darc['no races']}</td><td>{count_darc['timeout']}</td><td>{count_darc['errors']}</td></tr>"
    table_html += f"<tr><td>O2/Coderrect</td><td>{count_coderrect['races']}</td><td>{count_coderrect['no races']}</td><td>{count_coderrect['timeout']}</td><td>{count_coderrect['errors']}</td></tr>"
    table_html += f"<tr><td>ThreadSanitizer</td><td>{count_threadsanitizer['races']}</td><td>{count_threadsanitizer['no races']}</td><td>{count_threadsanitizer['timeout']}</td><td>{count_threadsanitizer['errors']}</td></tr>"
    table_html += f"<tr><td>Helgrind</td><td>{count_helgrind['races']}</td><td>{count_helgrind['no races']}</td><td>{count_helgrind['timeout']}</td><td>{count_helgrind['errors']}</td></tr>"
    table_html += '</table>'
    
    return table_html

if __name__ == '__main__':
    table = generate_table()
    with open('index_summary.html', 'w') as f:
        f.write(table)

# Remove all *.o files
os.system(f"rm -rf ./*.o")
