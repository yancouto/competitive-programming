// Only way to easily get rust-analyzer on all rs files everywhere while opening the folder.

fn main() {
    // Read the directory and generate mod declarations
    let mut mod_declarations = String::new();
    let mut count = 0;
    for entry in glob::glob("*/**/*.rs").unwrap() {
        count += 1;
        let path = entry.unwrap().to_path_buf();
        if path.extension() == Some(std::ffi::OsStr::new("rs")) && !path.starts_with("target") {
            mod_declarations.push_str(&format!(
                "#[path = r\"{}\"] pub mod a{};\n",
                path.to_string_lossy(),
                count
            ));
        }
    }

    // Write the mod declarations to a file
    std::fs::write("fake_main.rs", mod_declarations).unwrap();
}
