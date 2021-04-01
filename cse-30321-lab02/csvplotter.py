import pandas as pd
import matplotlib.pyplot as plt


fns = ["dogs_cats_birds_model_case01_30epoch.csv", "dogs_cats_birds_model_case02_30epoch.csv", "dogs_cats_birds_model_case03_30epoch.csv"]
#  fns = ["dogs_cats_birds_model_case01_100epoch.csv", "dogs_cats_birds_model_case02_100epoch.csv", "dogs_cats_birds_model_case03_100epoch.csv"]


plt.title("Case Training Accuracy Each Iteration")
plt.xlabel("Epoch Number")
plt.ylabel("Accuracy")

for fn in fns:
    df = pd.read_csv(fn)

    plt.scatter(range(1,len(df)+1), df["accuracy"], label=f'{fns.index(fn)+1}')
    plt.plot(range(1,len(df)+1), df["accuracy"])

    
plt.legend(title="Case")
plt.savefig("Case_Accuracy_Chart.png")

plt.clf()

plt.title("Case Validation Accuracy Each Iteration")
plt.xlabel("Epoch Number")
plt.ylabel("Accuracy")

for fn in fns:
    df = pd.read_csv(fn)

    plt.scatter(range(1,len(df)+1), df["val_accuracy"], label=f'{fns.index(fn)+1}')
    plt.plot(range(1,len(df)+1), df["val_accuracy"])

    
plt.legend(title="Case")
plt.savefig("Case_Validation_Accuracy_Chart.png")



'''
# for individual cases....
# case 1
fn = "dogs_cats_birds_model_case01_30epoch.csv"

df = pd.read_csv(fn)

plt.scatter(range(1,31), df["accuracy"])
plt.plot(range(1,31), df["accuracy"])

plt.title("Case 1 Training Accuracy Each Iteration")
plt.xlabel("Epoch Number")
plt.ylabel("Accuracy")

plt.savefig("Case_1_Chart.png")



# case 2
fn = "dogs_cats_birds_model_case02_30epoch.csv"

df = pd.read_csv(fn)

plt.scatter(range(1,31), df["accuracy"])
plt.plot(range(1,31), df["accuracy"])

plt.title("Case 2 Training Accuracy Each Iteration")
plt.xlabel("Epoch Number")
plt.ylabel("Accuracy")

plt.savefig("Case_2_Chart.png")


# case 3
fn = "dogs_cats_birds_model_case03_30epoch.csv"

df = pd.read_csv(fn)

plt.scatter(range(1,31), df["accuracy"])
plt.plot(range(1,31), df["accuracy"])

plt.title("Case 3 Training Accuracy Each Iteration")
plt.xlabel("Epoch Number")
plt.ylabel("Accuracy")

plt.savefig("Case_3_Chart.png")
'''
