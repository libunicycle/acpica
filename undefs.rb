#!/usr/bin/ruby

result = []

for l in IO.readlines("undefs.txt")
  if l =~ /undefined reference to `(.*?)'/
    sym = $1

    files = `git grep -l -e '^#{sym} ('`
    for f in files.split
      if f =~ %r{source/components/(.*)$}
        result << $1
      end
    end
  end
end

result.uniq!
puts result
