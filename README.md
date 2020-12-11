# IDP
This is the repository for the Independent Design Project 2020, developed by @barkermrl, @moonear2000. This repository has now been archived after the final competition.

## Guide to Contributing
Please branch off main when implementing a feature. Work on the branch locally, committing as needed. When the feature is complete, rebase off master (ensuring you fetch the latest version from origin) and submit a pull request to merge into main.

Please work in a python virtual environment (creating using anaconda or pip etc.) and install the python packages for this project, run:
```
pip install -r requirements.txt
```
If you add any python packages to the project, ensure you add them to the requirements file using pip:
```
pip freeze > requirements.txt
```

Platformio can be installed as an extension for most common IDEs such as VS Code and CLion. The supported editors can be found [here](https://platformio.org/install/integration) and the documentation can be found [here](https://docs.platformio.org/en/latest/what-is-platformio.html). Note the CLI tool is installed automatically via pip so can be used to suplement the IDE interface.

Flowchart.png gives the overall architecture of the program and can be edited online [here](https://viewer.diagrams.net/?highlight=0000ff&edit=_blank&layers=1&nav=1&title=IDP_flowchart.drawio#R7V1bc9o4FP41PHYH32TzmFuTnWmnncl22z51hC2wN8aitgihv34lIxs4MrG4%2BJJLHoIlCxvO9%2BncdGQG1tXs6TbF8%2FAzDUg8MIfB08C6HpimYZuIv4ie1brHG1rrjmkaBXLQpuM%2B%2BkNk51D2LqKAZDsDGaUxi%2Ba7nT5NEuKznT6cpnS5O2xC4927zvGUKB33Po7V3u9RwELZa6DR5sQdiaahvLVnuusTM1wMlt8kC3FAl1td1s3AukopZeuj2dMViYXwCrms3%2Fdxz9nyg6UkYTpviONvn%2F717sjMuLk0kt%2Br3xcT8sEwvPV1HnG8kF9Zfly2KmSQ0kUSEHEZY2BdLsOIkfs59sXZJUed94VsFsvT5dcc8sY0xlkmj306i3x5PKEJk1gbtmhHcXxFY5ryjoQmvP8ywFlY3jNjKX0gxYiBaQ3zP35GlYIUzCNJGXna6pJSuSV0Rli64kPk2RKhkqLr5nKDt23LvnALalS8D0uOTctLb2DgBxKJg1AZvXlU3GEtKmbbqLgvAZUzyN5w6kRvIKch0bPvEb01kP%2Fz1%2FjbxS%2Fn8%2FLD3fKDoQj%2BnuGUnSb9bUFy8gYO8QK7itaeObYQqoDiDKK2d1letrdlbVbQ3G6M5YqoP9NHIsxuyKU7DfOjvL3gFjdWIOCcnovDeUp9IghdB8MY%2Bw%2FTHLgvCxZHCZH9GyyH55gqAmFMvIlfhTDyPTKeNIKoZXaNqKkgepEKAJfiH2YloFHCSJpxJyqiycD6qE6ukM7GCw1Ea2CYTAjyK2EI3NH4XPYDwGAPNWHwmoLB2jexcM70EgY%2FSv1YHCwSFsW5axvHUSZAeZ9rAGTL01CfqFX1adf7CCQJLkRowlu%2BkK6Q6XPzZ6%2BgMrpIfVJvN7mtnBJWr%2FRJsBMMqWLfEqtTIdWiLyUxZtHjbghVJWp5h6%2BU654Nqg5wyB3oV6y%2Ft3zXdsgDL%2BQCJeCCC60Fo1woR7782ieQAXVEhudAriWD2SsyGBBD40gyGIBVFtQBTZNBI3pojwymJhmsfpFhBDTDsWQwQXRpIj0ycHTwamvYXAzI9n9geJ8ikXDo59pwcf0JzspMS3VNvnAb%2FBgRTsQLhaTcNrNdWuI4miaCs0S4kLxDWPDIx%2FGFPDGLgkC8%2FTIlWfQHj%2FNLCS9Cyo9f17kcONfiWgtGM0lxwPhRI9GtU%2BEyDCsobDXmGKpW4pVGt4auE96Ye2ZpJNaErruXTZqykE5pguObTS9wlzdjPlE6l%2BL%2FjzC2ktIUlN6vx59lda0et1xdRe5panJtFX0aEKo1lOHQWHSIF%2Bo%2FZAo4bz7ksYd9m1O2mjLqw5ziIk5XP%2BT18sZP0fjLKZrXT9snr1eydcJc9DTnoq3rVZ3oLrkO4AoMpBp2eS11cUlO8pQE73N8%2F9oH6t0cV13EG5GzOslDqUkTej6pThOOPcd2zpQmNIZm72TdQAqJPEXshzwnjrdUIW9tNKFoFIqwAwWKdJ0ZV1OBthOWIsCh0kYfGpYikOywnHYVtq2GIn9ff%2BUd93TCljhfNvgY06UfVsUnXQWGpnMm10oJVxRNUC4PtKMJ1GjlmjAcxbn1xPGUphELZ28gSC%2BzgNta2W0zSnc0CmXa9XKfp32tsi1US62ydXSV7WFa9NBUmgUXVndTac2kxlzV7%2BkY9RPzvtqou3YvUHe8DlAvhLSF%2BvcwXyn3uRe6SMX7s0GxYJtHMa9hwRxIuvMVc9dUYLjD6xwRZaGaKhqOCUn4S0BizkcRYr54UJSl0M5BcXQ0on50cqIRs3Rt2FBTm7W0wo32wHpwwGCAyKPlgMFRA4arECdTMS2DKJXFRO8JHlhyDKwa6jzpgFST916edCrMMI%2FXfXkSUk3qP%2FgBZGQF1pT%2F40aWCF8niwLyDm7dHC5NdXdz2DmraT410tBdmSw42RPbjIotMYVJHR1rmxG4UMsFR6hX1WfadChcitdGB2sELgRd9DOVHMEsZl3JERxfJLMbjbBRr4rhCg30drnp1sQjTasqneRqa3RwdelQuG49oQMsdzaPtlzmHr%2F1zKoKQReqRlXB8a1URzqqqrrDItuEFa8ZxynBgZCAzERl4uXFJ6Ggp9v9XpqC6P3QF472snWv1IUNZjmCs1xXXcALKbifq5j6eU%2Bldnwr6qJYN9lZs83z0YPdhLVC2DcfUcNkt915RO32KqLW9kt6pmfgpo2jt3PByEZzO9epa46F26GrZw4d34pe8sxeUdnWpHLB%2BZ5wGUEKQlOn7WKDSWHDwpWGIy6vV5rtlYJsgCV1t%2BX6a08Nq29FYl84DgOZ5M8qtxq9eV9EqQvu%2FskchcZ4U1UpLqz%2F6Tz2HKnbXXarUnb3NlQXpQxfGSzd16WMVP%2Fmle5Q6D4sGqkrS9sx7ntwqzFjukfRGPZqgbBIpteGBIUd7Im36MEt%2FrAES9db9MBuPWUXSdMPqDBUB6NDPoy0%2BdCvRTkliwWzFEc%2Fvabl6MEwdDb2tscH3Sx74aD1hA8ejCaPXZXzYMqg7QfYGKqL1SUfdJ9n1LNVWqjmj679dff5hWdOh8L71K3SwvGtpDcN47x16W2R09N9LEdL5ISF6cc%2BYGkEC9MbesDSCH7gGnLC8S2Rs6unAj7LufrHApo9M6WwTOnYlaRRnY%2FWuCntVfq9ZxGVsmB4tBICMOvm3w9WQnseLdiwUqnae0PyzP4yyjORPp3NFyzPyjy%2BuC0ak8nE3JPIRGPkoPOkZew9DNl5Glyrm%2F5Lpbv9EIZNXj%2BlYyqot%2FXg5vUSzotP9SuJzu5z%2FYbZK6%2BypEZ9DGz2SqOjc%2BXIUNc5MrNXhrtvDhqsnDll5bwd063cqB3bbWqk3rv%2FKZFGf%2BBlBLhS9SsjVYb3mF8Z4c3NDy2tQdz8XJV18z8%3D).

## Repository Structure
This repository contains the following directories:

`.github/workflows/`  
Contains two workflow files which run PlatformIO and Pytest tests whenever code is pushed or a pull request is submitted.

`build/`  
Contains the compiled code for an Arduino Uno WiFi Rev2 board. This is generated automatically when PlatformIO builds the code.

`docs/`  
Contains markdown files which is used to generate documentation for this software. These can be viewed on the [GitHub pages site](https://barkermrl.github.io/IDP/).

`include/`  
This directory is intended for PlatformIO project header files.

`lib/`  
This directory is intended for project specific (private) libraries. PlatformIO will compile them to static libraries and link into executable file.

`python/`  
Contains the python code used for implementing computer vision in the robot.

`src/`  
Contains the C++ source code which is compiled by PlatformIO and uploaded to the Arduino board.

`test/`
This directory is intended for PlatformIO Unit Testing and project tests.
